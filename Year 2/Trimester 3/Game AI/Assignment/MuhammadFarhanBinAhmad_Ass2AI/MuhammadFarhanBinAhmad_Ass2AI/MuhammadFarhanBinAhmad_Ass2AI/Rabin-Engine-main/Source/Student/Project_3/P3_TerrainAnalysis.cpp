#include <pch.h>
#include "Terrain/TerrainAnalysis.h"
#include "Terrain/MapMath.h"
#include "Agent/AStarAgent.h"
#include "Terrain/MapLayer.h"
#include "Projects/ProjectThree.h"

#include <iostream>


const float FOV = 160.f;
const float FOVDeg = 185;
const float FOVRad = FOVDeg * PI / 180.f;
const float MAXFLOAT = std::numeric_limits<float>::max();

bool isNeighbourVisible(int r, const int& row_limit, int c, const int& column_limit, int row, int col)
{
    for (int i = std::max(0, r - 1); i <= std::min(r + 1, row_limit - 1); i++)
    {
        for (int j = std::max(0, c - 1); j <= std::min(c + 1, column_limit - 1); j++)
        {
            if (r != i || c != j)
            {
                if (is_clear_path(i, j, row, col))
                {
                    int dx = r - i;
                    int dy = c - j;

                    if (!terrain->is_wall(i, j + dy) && !terrain->is_wall(i + dx, j))
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
bool ProjectThree::implemented_fog_of_war() const // extra credit
{
    return false;
}
void DebugGrid(const Vec2& pos)
{
    std::cout << pos.x << ',' << pos.y << '\n';
}
float distance_to_closest_wall(int row, int col)
{
    /*
        Check the euclidean distance from the given cell to every other wall cell,
        with cells outside the map bounds treated as walls, and return the smallest
        distance.  Make use of the is_valid_grid_position and is_wall member
        functions in the global terrain to determine if a cell is within map bounds
        and a wall, respectively.
    */
    std::list<std::pair<int, int>> Walls;
    float bestDistanceSquared = MAXFLOAT;

    // Get  distance between tiles in  map.
    const Vec3 dist = terrain->get_world_position(0, 0) - terrain->get_world_position(1, 1);

    for (short r = -1; r <= terrain->get_map_height(); r++)
    {
        for (short c = -1; c <= terrain->get_map_width(); c++)
        {
            if (row == r && col == c)
            {
                continue;
            }
            // If position is invalid
            if (!terrain->is_valid_grid_position(r, c))
            {
                std::pair<int, int> wall = std::make_pair(r,c);
                Walls.push_back(wall);
            }
            // If position is a wall
            else if (terrain->is_wall(r, c))
            {
                std::pair<int, int> wall = std::make_pair(r, c);
                Walls.push_back(wall);
            }
        }
    }

    // Now we do BSF to find closest distance
    for (auto& gridPos : Walls)
    {
        float xDiff = static_cast<float>(gridPos.first - row);
        float yDiff = static_cast<float>(gridPos.second - col);

        float currentDistanceSquared = (xDiff * xDiff) + (yDiff * yDiff);

        if (bestDistanceSquared > currentDistanceSquared)
        {
            bestDistanceSquared = currentDistanceSquared;
        }
    }

    return bestDistanceSquared;

}

bool is_clear_path(int row0, int col0, int row1, int col1)
{
    /*
        Two cells (row0, col0) and (row1, col1) are visible to each other if a line
        between their centerpoints doesn't intersect the four boundary lines of every
        wall cell.  You should puff out the four boundary lines by a very tiny amount
        so that a diagonal line passing by the corner will intersect it.  Make use of the
        line_intersect helper function for the intersection test and the is_wall member
        function in the global terrain to determine if a cell is a wall or not.
    */
    int smallerRow = 0;
    int smallerCol = 0;
    int largerRow = 0;
    int largerCol = 0;

    if (row0 < row1)
    {
        smallerRow = row0;
        largerRow = row1;
    }
    else
    {
        smallerRow = row1;
        largerRow = row0;
    }

    if (col0 < col1)
    {
        smallerCol = col0;
        largerCol = col1;
    }
    else
    {
        smallerCol = col1;
        largerCol = col0;
    }

    // Store walls here.
    std::list<std::pair<int, int>> Walls;

     float worldDist= std::abs(terrain->get_world_position(0, 0).x - terrain->get_world_position(1, 1).x);
     float halfDist = worldDist / 2.0f;
     float puffValue = 0.001f;
     float moveValue = halfDist + (puffValue * worldDist);

    const Vec3& v3_point0 = terrain->get_world_position(row0, col0);
    const Vec3& v3_point1 = terrain->get_world_position(row1, col1);
    Vec2 point0 = { v3_point0.x, v3_point0.z };
    Vec2 point1 = { v3_point1.x, v3_point1.z };

    // Go through square and make check for walls
    for (int r = smallerRow; r <= largerRow; r++)
    {
        for (int c = smallerCol; c <= largerCol; c++)
        {
            if (terrain->is_wall(r, c))
            {
                std::pair<int, int> pos = std::make_pair(r, c);
                Walls.push_back(pos);
            }
        }
    }


    for (auto& wall : Walls)
    {
        const auto& worldPos = terrain->get_world_position(wall.first, wall.second);

        std::list<Vec2> points;

        points.push_back({ worldPos.x + moveValue, worldPos.z + moveValue });
        points.push_back({ worldPos.x - moveValue, worldPos.z + moveValue });
        points.push_back({ worldPos.x - moveValue, worldPos.z - moveValue });
        points.push_back({ worldPos.x + moveValue, worldPos.z - moveValue });
        points.push_back({ worldPos.x + moveValue, worldPos.z + moveValue });

        for (auto it = std::next(points.begin()); it != points.end(); it++) 
        {
            auto prev = std::prev(it);
            if (line_intersect(point0, point1, *prev, *it)) 
            {
                return false;
            }
        }
    }

    return true;
}

void analyze_openness(MapLayer<float> &layer)
{
    /*
        Mark every cell in the given layer with the value 1 / (d * d),
        where d is the distance to the closest wall or edge.  Make use of the
        distance_to_closest_wall helper function.  Walls should not be marked.
    */
    for (int r = 0; r < terrain->get_map_height(); r++)
    {
        for (int c = 0; c < terrain->get_map_width(); c++)
        {
            if (!terrain->is_wall(r, c))
            {
                float closestDistance = distance_to_closest_wall(r, c);
                layer.set_value(r, c, 1 / closestDistance);
            }
        }
    }
    // WRITE YOUR CODE HERE


}
void analyze_visibility(MapLayer<float> &layer)
{
    /*
        Mark every cell in the given layer with the number of cells that
        are visible to it, divided by 160 (a magic number that looks good).  Make sure
        to cap the value at 1.0 as well.

        Two cells are visible to each other if a line between their centerpoints doesn't
        intersect the four boundary lines of every wall cell.  Make use of the is_clear_path
        helper function.
    */


    for (int r = 0; r < terrain->get_map_height();  r++)
    {
        for (int c = 0; c < terrain->get_map_width(); c++)
        {
            // Check against other grid.
            int numVisibleCells = 0;

            // If this is a wall, just skip
            if (terrain->is_wall(r, c))
            {
                continue;
            }

            // We check against every other cell in the grid.
            for (int other_r = 0; other_r < terrain->get_map_width(); other_r++)
            {
                for (int other_c = 0; other_c < terrain->get_map_height(); other_c++)
                {
                    if (is_clear_path(r, c, other_r, other_c))
                    {
                        numVisibleCells++;
                    }
                }
            }
            layer.set_value(r, c, std::min(numVisibleCells / FOV, 1.0f));
        }
    }
    // WRITE YOUR CODE HERE
}

void analyze_visible_to_cell(MapLayer<float> &layer, int row, int col)
{
    /*
        For every cell in the given layer mark it with 1.0
        if it is visible to the given cell, 0.5 if it isn't visible but is next to a visible cell,
        or 0.0 otherwise.

        Two cells are visible to each other if a line between their centerpoints doesn't
        intersect the four boundary lines of every wall cell.  Make use of the is_clear_path
        helper function.
    */
    for (int r = 0; r < terrain->get_map_height(); r++)
    {
        for (int c = 0; c < terrain->get_map_width(); c++)
        {
            // If this is a wall, just skip
            if (terrain->is_wall(r, c))
            {
                continue;
            }

            if (is_clear_path(r, c, row, col))
            {
                layer.set_value(r, c, 1.0f);
            }
            else
            {
                int row_limit = terrain->get_map_width();
                int column_limit = terrain->get_map_height();

                if (isNeighbourVisible(r, row_limit, c, column_limit, row, col))
                {
                    layer.set_value(r, c, 0.5f);
                }
                else
                {
                    layer.set_value(r, c, 0.0f);
                }
            }
        }
    }
    // WRITE YOUR CODE HERE
}

void analyze_agent_vision(MapLayer<float> &layer, const Agent *agent)
{
    /*
        For every cell in the given layer that is visible to the given agent,
        mark it as 1.0, otherwise don't change the cell's current value.

        You must consider the direction the agent is facing.  All of the agent data is
        in three dimensions, but to simplify you should operate in two dimensions, the XZ plane.

        Take the dot product between the view vector and the vector from the agent to the cell,
        both normalized, and compare the cosines directly instead of taking the arccosine to
        avoid introducing floating-point inaccuracy (larger cosine means smaller angle).

        Give the agent a field of view slighter larger than 180 degrees.

        Two cells are visible to each other if a line between their centerpoints doesn't
        intersect the four boundary lines of every wall cell.  Make use of the is_clear_path
        helper function.
    */
    auto AgentView_3d = agent->get_forward_vector();
    Vec2 agentView = { AgentView_3d.x, AgentView_3d.z };
    float FoVRad = FOVDeg * PI / 180.1f;

    // For each grid.
    for (int r = 0; r < terrain->get_map_height(); r++)
    {
        for (int c = 0; c < terrain->get_map_width(); c++)
        {
            if (terrain->is_wall(r, c))
            {
                continue;
            }

            // Vector from agent to cell
            Vec3 agentToCell = { terrain->get_world_position(r, c) - agent->get_position() };
            Vec2 agentToCellNorm = { agentToCell.x, agentToCell.z };

            agentToCell.Normalize();
            agentView.Normalize();

            float dotProuct = agentToCellNorm.Dot(agentView);

            if (dotProuct > std::cos(FoVRad))
            {
                // Now we check if we can see node
                GridPos& agentPos = terrain->get_grid_position(agent->get_position());
                if (is_clear_path(r, c, agentPos.row, agentPos.col))
                {
                    layer.set_value(r, c, 1.0f);
                }
            }
        }
    }
    // WRITE YOUR CODE HERE
}
bool IsLayerEmpty(MapLayer<float>& layer)
{
    for (int r = 0; r < terrain->get_map_height(); r++)
    {
        for (int c = 0; c < terrain->get_map_width(); c++)
        {
            float value = layer.get_value(r, c);
            if (value != 0)
            {
                return false;
            }
        }
    }
    return true;
}
float GetDecayFormula(float oldinfluence, float dist, float decay)
{
    return oldinfluence * exp(-1 * dist * decay);
}
float GetDistance(int r, int c, int other_r, int other_c)
{
    return Vec2::Distance({ static_cast<float>(r), static_cast<float>(c) }, { static_cast<float>(other_r), static_cast<float>(other_c)});
}

void propagate_solo_occupancy(MapLayer<float> &layer, float decay, float growth)
{
    /*
        For every cell in the given layer:

            1) Get the value of each neighbor and apply decay factor
            2) Keep the highest value from step 1
            3) Linearly interpolate from the cell's current value to the value from step 2
               with the growing factor as a coefficient.  Make use of the lerp helper function.
            4) Store the value from step 3 in a temporary layer.
               A float[40][40] will suffice, no need to dynamically allocate or make a new MapLayer.

        After every cell has been processed into the temporary layer, write the temporary layer into
        the given layer;
    */
    if (IsLayerEmpty(layer))
    {
        return;
    }
    //bit too late to change to [40][40]
    //ahh lazy change
    std::vector<std::vector<float>> tempLayer(terrain->get_map_height(), std::vector<float>(terrain->get_map_width(), 0.0f));

    for (int r = 0; r < terrain->get_map_height(); r++)
    {
        for (int c = 0; c < terrain->get_map_width(); c++)
        {
            // Continue loop if is wall
            if (terrain->is_wall(r, c))
            {
                continue;
            }

            float maxDecay = 0;
            for (int other_r = std::max(0, r - 1); other_r <= std::min(r + 1, terrain->get_map_width() - 1); other_r++)
            {
                for (int other_c = std::max(0, c - 1); other_c <= std::min(c + 1, terrain->get_map_height() - 1); other_c++)
                {
                    // Exclude the current node
                    if (r != other_r || c != other_c)
                    {
                        int dx = r - other_r;
                        int dy = c - other_c;

                        if (!!terrain->is_wall(other_r + dx, other_c) || !terrain->is_wall(other_r, other_c + dy))
                        {
                            float dist = GetDistance(r, c, other_r, other_c);
                            float nodeDecay = GetDecayFormula(layer.get_value(other_r, other_c), dist, decay);
                            // Record maxDecay
                            if (maxDecay < nodeDecay)
                            {
                                maxDecay = nodeDecay;
                            }
                        }
                    }
                }
            }

            // Apply linear interpolation
            float res = lerp(layer.get_value(r, c), maxDecay, growth);

            // Store in tempLayer
            tempLayer[r][c] = res;
        }
    }

    for (int r = 0; r < terrain->get_map_height(); r++)
    {
        for (int c = 0; c < terrain->get_map_width(); c++)
        {
            layer.set_value(r, c, tempLayer[r][c]);
        }
    }
    // WRITE YOUR CODE HERE
}
//Dont do
void propagate_dual_occupancy(MapLayer<float> &layer, float decay, float growth)
{
    /*
        Similar to the solo version, but the values range from -1.0 to 1.0, instead of 0.0 to 1.0

        For every cell in the given layer:

        1) Get the value of each neighbor and apply decay factor
        2) Keep the highest ABSOLUTE value from step 1
        3) Linearly interpolate from the cell's current value to the value from step 2
           with the growing factor as a coefficient.  Make use of the lerp helper function.
        4) Store the value from step 3 in a temporary layer.
           A float[40][40] will suffice, no need to dynamically allocate or make a new MapLayer.

        After every cell has been processed into the temporary layer, write the temporary layer into
        the given layer;
    */

    // WRITE YOUR CODE HERE
}
void updateMaximumValue(float& value, float& maximumValue)
{
    if (maximumValue < value)
    {
        maximumValue = value;
    }
}
void divideByMaximumValue(float& value, float maximumValue)
{
    value = value / maximumValue;
}
void updateLowestNegativeValue(float& value, float& lowestNegative)
{
    if (value < 0 && value < lowestNegative)
    {
        lowestNegative = value;
    }
}
void normalizePositiveValue(float& value, float maximumValue)
{
    if (value > 0)
    {
        value = value / maximumValue;
    }
}

void normalizeNegativeValue(float& value, float lowestNegative)
{
    if (value < 0)
    {
        value = value / lowestNegative;
        value *= -1;
    }
}
void normalize_solo_occupancy(MapLayer<float> &layer)
{
    /*
        Determine the maximum value in the given layer, and then divide the value
        for every cell in the layer by that amount.  This will keep the values in the
        range of [0, 1].  Negative values should be left unmodified.
    */
    float maximumValue = 0;
    auto boundUpdateMaximumValue = [&maximumValue](float& value) { updateMaximumValue(value, maximumValue); };
    layer.for_each(boundUpdateMaximumValue);

    if (maximumValue == 0)
    {
        return;

    }
    auto boundDivideByMaximumValue = [maximumValue](float& value) { divideByMaximumValue(value, maximumValue); };
    layer.for_each(boundDivideByMaximumValue);
    // WRITE YOUR CODE HERE
}
void normalize_dual_occupancy(MapLayer<float> &layer)
{
    /*
        Similar to the solo version, but you need to track greatest positive value AND 
        the least (furthest from 0) negative value.

        For every cell in the given layer, if the value is currently positive divide it by the
        greatest positive value, or if the value is negative divide it by -1.0 * the least negative value
        (so that it remains a negative number).  This will keep the values in the range of [-1, 1].
    */
    bool isEmpty = true;
    for (int r = 0; r < terrain->get_map_width(); r++)
    {
        for (int c = 0; c < terrain->get_map_height(); c++)
        {
            float value = layer.get_value(r, c);
            if (value != 0)
            {
                isEmpty = false;
                break;
            }
        }
        if (!isEmpty)
        {
            break;
        }
    }

    if (isEmpty)
    {
        return;
    }

    float maximumValue = 0;
    float lowestNegative = 0;
    auto boundUpdateMaximumValue = [&maximumValue](float& value) { updateMaximumValue(value, maximumValue); };
    auto boundUpdateLowestNegativeValue = [&lowestNegative](float& value) { updateLowestNegativeValue(value, lowestNegative); };
    layer.for_each(boundUpdateMaximumValue);
    layer.for_each(boundUpdateLowestNegativeValue);

    if (maximumValue == 0)
    {
        return;
    }

    // Normalize values in the layer
    auto boundNormalizePositiveValue = [maximumValue](float& value) { normalizePositiveValue(value, maximumValue); };
    auto boundNormalizeNegativeValue = [lowestNegative](float& value) { normalizeNegativeValue(value, lowestNegative); };
    layer.for_each([boundNormalizePositiveValue, boundNormalizeNegativeValue](float& value) {
        if (value > 0) 
        {
            boundNormalizePositiveValue(value);
        }
        else if (value < 0) 
        {
            boundNormalizeNegativeValue(value);
        }
        });
    // WRITE YOUR CODE HERE
}

void enemy_field_of_view(MapLayer<float> &layer, float fovAngle, float closeDistance, float occupancyValue, AStarAgent *enemy)
{
    /*
        First, clear out the old values in the map layer by setting any negative value to 0.
        Then, for every cell in the layer that is within the field of view cone, from the
        enemy agent, mark it with the occupancy value.  Take the dot product between the view
        vector and the vector from the agent to the cell, both normalized, and compare the
        cosines directly instead of taking the arccosine to avoid introducing floating-point
        inaccuracy (larger cosine means smaller angle).

        If the tile is close enough to the enemy (less than closeDistance),
        you only check if it's visible to enemy.  Make use of the is_clear_path
        helper function.  Otherwise, you must consider the direction the enemy is facing too.
        This creates a radius around the enemy that the player can be detected within, as well
        as a fov cone.
    */
    for (int r = 0; r < terrain->get_map_height();r++)
    {
        for (int c = 0; c < terrain->get_map_width(); c++)
        {
            // If value is negative
            if (layer.get_value(r, c) < 0)
            {
                // Set to 0
                layer.set_value(r, c, 0);
            }
        }
    }
    Vec3 AgentView_3d = enemy->get_forward_vector();
    Vec2 agentView = { AgentView_3d.x, AgentView_3d.z };
    agentView.Normalize();

    for (int r = 0; r < terrain->get_map_height(); r++)
    {
        for (int c = 0; c < terrain->get_map_width(); c++)
        {
            //if wall then skp
            if (terrain->is_wall(c, r))
            {
                continue;
            }
            if (Vec3::Distance(enemy->get_position(), terrain->get_world_position(r, c)) < closeDistance)
            {
                GridPos enemyGridPos = terrain->get_grid_position(enemy->get_position());
                if (is_clear_path(r, c, enemyGridPos.row, enemyGridPos.col))
                {
                    layer.set_value(r, c, occupancyValue);
                }
            }
            //use FOV
            else
            {
                Vec3 agentToGrid = terrain->get_world_position(r, c) - enemy->get_position();
                Vec2 agentToGridNorm;
                agentToGridNorm.x = agentToGrid.x;
                agentToGridNorm.y = agentToGrid.z;

                agentToGrid.Normalize();

                float dotProd = agentToGridNorm.Dot(agentView);

                if (dotProd > cos(FOVRad))
                {
                    GridPos agentPos = terrain->get_grid_position(enemy->get_position());
                    if (is_clear_path(r, c, agentPos.row, agentPos.col))
                    {
                        layer.set_value(r, c, occupancyValue);
                    }
                }

            }
        }
    }

    // WRITE YOUR CODE HERE
}

bool enemy_find_player(MapLayer<float> &layer, AStarAgent *enemy, Agent *player)
{
    /*
        Check if the player's current tile has a negative value, ie in the fov cone
        or within a detection radius.
    */
    const Vec3& playerWorldPos = player->get_position();
    GridPos playerGridPos = terrain->get_grid_position(playerWorldPos);

    if (terrain->is_valid_grid_position(playerGridPos) )
    {
        if (layer.get_value(playerGridPos) < 0.0f)
        {
            return true;
        }
    }
    
    return false;
}

bool enemy_seek_player(MapLayer<float>& layer, AStarAgent* enemy)
{
    /*
        Attempt to find a cell with the highest nonzero value (normalization may
        not produce exactly 1.0 due to floating point error), and then set it as
        the new target, using enemy->path_to.

        If there are multiple cells with the same highest value, then pick the
        cell closest to the enemy.

        Return whether a target cell was found.
    */
    std::list<GridPos> gridPosList;
    float maximumValue = MAXFLOAT;
    GridPos agentPos = terrain->get_grid_position(enemy->get_position());

    for (int r = 0; r < terrain->get_map_height(); r++)
    {
        for (int c = 0; c < terrain->get_map_width(); c++)
        {
            if (r == agentPos.row && c == agentPos.col)
            {
                continue;
            }
            float value = std::abs(layer.get_value(r, c));
            if (value == maximumValue)
            {
                GridPos temp;
                temp.row = r;
                temp.col = c;
                gridPosList.push_back(temp);
            }
            // New max discovered
            if (value > maximumValue)
            {
                // Clear array
                gridPosList.clear();
                GridPos temp;
                temp.row = r;
                temp.col = c;
                gridPosList.push_back(temp);
                maximumValue = value;
            }
        }
    }
    if (gridPosList.size() > 0)
    {
        // Find the closest to player
        float curMinDistance = MAXFLOAT;
        Vec3 currMinDistPos;
        for (const GridPos& gridPosition : gridPosList)
        {
            Vec3 worldPosNode = terrain->get_world_position(gridPosition);
            float dist = Vec3::Distance(enemy->get_position(), worldPosNode);
            if (dist < curMinDistance)
            {
                curMinDistance = dist;
                currMinDistPos = worldPosNode;
            }
        }
        enemy->path_to(currMinDistPos);
        return true;
    }
    else
    {
        return false;
    }
}
    // WRITE YOUR CODE HERE}
