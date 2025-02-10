package edu.singaporetech.fourdigits

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.ui.Modifier
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import edu.singaporetech.fourdigits.ui.theme.FourdigitsTheme
import androidx.compose.foundation.layout.*
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.platform.testTag
import androidx.compose.ui.unit.dp
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.grid.GridCells
import androidx.compose.foundation.lazy.grid.LazyVerticalGrid
import androidx.compose.ui.Alignment
import androidx.lifecycle.ViewModelProvider
import androidx.navigation.NavController

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val database = FourDigitRoomDatabase.getDatabase(this)
        val repository = FourDigitRepository(database.fourDigitDao(), dataStore = this.dataStore)
        val viewModelFactory = FourDigitViewModelFactory(repository)
        val viewModel = ViewModelProvider(this, viewModelFactory)[FourDigitViewModel::class.java]


        setContent {
            val navController = rememberNavController()
            FourdigitsTheme {
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    NavHost(
                        navController = navController,
                        startDestination = "generator_screen"
                    ) {
                        composable("generator_screen") {
                            GeneratorScreen(
                                navController,
                                viewModel
                            )
                        }
                        composable("display_screen") {
                            DisplayScreen(navController, viewModel)
                        }
                    }
                }
            }
        }
    }
}

@Composable
fun GeneratorScreen(navController: NavController, viewModel: FourDigitViewModel) {
    var number by remember { mutableStateOf(viewModel.lastGeneratedNumber.toString()) }

    Column(
        modifier = Modifier
            .fillMaxSize()
            .padding(16.dp),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {

        if(number != "0") {
            Text(
                text = number,
                modifier = Modifier
                    .testTag("FourDigit")
                    .padding(bottom = 32.dp),
                style = MaterialTheme.typography.headlineLarge
            )
        }
        else {
            Text(
                text = "",
                modifier = Modifier
                    .testTag("FourDigit")
                    .padding(bottom = 32.dp),
                style = MaterialTheme.typography.headlineLarge
            )
        }

        Button(
            onClick = {
                viewModel.generateNumber()
                number = viewModel.lastGeneratedNumber.toString()
            },
            modifier = Modifier
                .width(120.dp)
                .padding(bottom = 16.dp)
                .height(50.dp)
        ) {
            Text("Generate")
        }

        Button(
            onClick = {
                navController.navigate("display_screen")
            },
            modifier = Modifier.width(120.dp).height(50.dp)
        ) {
            Text("Display All")
        }
    }
}

@Composable
fun DisplayScreen(navController: NavController, viewModel: FourDigitViewModel) {
    val numbers by viewModel.allNumbers.collectAsState(initial = emptyList())
    val isGrid by viewModel.isGrid.collectAsState(initial = false)

    Scaffold(
        modifier = Modifier.fillMaxSize(),
        bottomBar = {
            BottomAppBar {
                Row(
                    modifier = Modifier.fillMaxWidth(),
                    horizontalArrangement = Arrangement.SpaceBetween,
                    verticalAlignment = Alignment.CenterVertically
                ) {

                    Row(verticalAlignment = Alignment.CenterVertically) {
                        Text(
                            text = "Grid View",
                            style = MaterialTheme.typography.bodyLarge,
                            modifier = Modifier.padding(5.dp)
                        )
                        Switch(
                            checked = isGrid,
                            onCheckedChange = { viewModel.toggleView(it) },
                            modifier = Modifier.testTag("GridSwitch")
                        )
                    }

                    Button(
                        onClick = { viewModel.clearNumbers() },
                        modifier = Modifier
                            .width(100.dp)
                            .height(50.dp)
                            .padding(bottom = 8.dp)
                    ) {
                        Text("Reset")
                    }
                }
            }
        }
    ) { paddingValues ->
        Column(
            modifier = Modifier
                .padding(paddingValues)
                .padding(16.dp)
        ) {
            if (!isGrid) {
                LazyColumn {
                    items(numbers.size) { index ->
                        val item = numbers[index]
                        Column(
                            Modifier
                                .fillMaxWidth()
                                .padding(8.dp)
                        ) {
                            Text("#${item.id}")
                            Text("${item.value}")
                        }
                        Divider()
                    }
                }
            } else {
                LazyVerticalGrid(
                    columns = GridCells.Fixed(4),
                    contentPadding = PaddingValues(8.dp)
                ) {
                    items(numbers.size) { index ->
                        val item = numbers[index]
                        Column(
                            Modifier.padding(8.dp),
                            horizontalAlignment = Alignment.CenterHorizontally
                        ) {
                            Text("#${item.id}")
                            Text("${item.value}")
                        }
                    }
                }
            }
        }
    }
}