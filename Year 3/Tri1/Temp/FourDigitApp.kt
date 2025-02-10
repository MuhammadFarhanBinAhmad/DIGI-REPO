package edu.singaporetech.fourdigits

import android.app.Application
import android.content.Context
import androidx.datastore.core.DataStore
import androidx.datastore.preferences.core.Preferences
import androidx.datastore.preferences.core.booleanPreferencesKey
import androidx.datastore.preferences.core.edit
import androidx.datastore.preferences.preferencesDataStore
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.viewModelScope
import androidx.room.Dao
import androidx.room.Database
import androidx.room.Entity
import androidx.room.Insert
import androidx.room.PrimaryKey
import androidx.room.Query
import androidx.room.Room
import androidx.room.RoomDatabase
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map
import kotlinx.coroutines.launch
import kotlin.random.Random

val Context.dataStore: DataStore<Preferences> by preferencesDataStore(name = "settings")

class FourDigitApp : Application() {
    override fun onCreate() {
        super.onCreate()
    }
}

@Entity(tableName = "four_digit_table")
data class FourDigit(
    @PrimaryKey(autoGenerate = true) val id: Int = 0,
    val value: Int
)

@Dao
interface FourDigitDao {
    @Insert
    suspend fun insert(fourDigit: FourDigit)

    @Query("SELECT * FROM four_digit_table ORDER BY id ASC")
    fun getAllNumbers(): Flow<List<FourDigit>>

    @Query("DELETE FROM four_digit_table")
    suspend fun deleteAll()

    @Query("DELETE FROM sqlite_sequence WHERE name = 'four_digit_table'")
    suspend fun resetIdCounter()
}

@Database(entities = [FourDigit::class], version = 1, exportSchema = false)
abstract class FourDigitRoomDatabase : RoomDatabase() {
    abstract fun fourDigitDao(): FourDigitDao

    companion object {
        @Volatile
        private var INSTANCE: FourDigitRoomDatabase? = null

        fun getDatabase(context: Context): FourDigitRoomDatabase {
            return INSTANCE ?: synchronized(this) {
                val instance = Room.databaseBuilder(
                    context.applicationContext,
                    FourDigitRoomDatabase::class.java,
                    "four_digit_database"
                ).build()
                INSTANCE = instance
                instance
            }
        }
    }
}

class FourDigitRepository(private val fourDigitDao: FourDigitDao,
                          private val dataStore: DataStore<Preferences>
) {
    val allNumbers: Flow<List<FourDigit>> = fourDigitDao.getAllNumbers()

    private object PrefKeys {
        val GRID_VIEW = booleanPreferencesKey("grid_view")
    }

    val isGrid: Flow<Boolean> = dataStore.data
        .map { preferences ->
            preferences[PrefKeys.GRID_VIEW] ?: false
        }

    suspend fun toggleGridView(enabled: Boolean) {
        dataStore.edit { prefs ->
            prefs[PrefKeys.GRID_VIEW] = enabled
        }
    }

    suspend fun insert(number: Int) {
        fourDigitDao.insert(FourDigit(value = number))
    }

    suspend fun deleteAll() {
        fourDigitDao.deleteAll()
    }

    suspend fun resetIdCounter() {
        fourDigitDao.resetIdCounter()
    }
}

class FourDigitViewModel(private val repository: FourDigitRepository) : ViewModel() {
    val allNumbers: Flow<List<FourDigit>> = repository.allNumbers
    val isGrid: Flow<Boolean> = repository.isGrid
    var lastGeneratedNumber = 0

    fun generateNumber() {
        val randomNumber = Random.nextInt(1000, 9999)
        viewModelScope.launch {
            repository.insert(randomNumber)
        }
        lastGeneratedNumber = randomNumber
    }

    fun clearNumbers() {
        viewModelScope.launch {
            repository.deleteAll()
            repository.resetIdCounter()
        }
        lastGeneratedNumber = 0
    }

    fun toggleView(enabled: Boolean) {
        viewModelScope.launch {
            repository.toggleGridView(enabled)
        }
    }
}

class FourDigitViewModelFactory(private val repository: FourDigitRepository) :
    ViewModelProvider.Factory {
    override fun <T : ViewModel> create(modelClass: Class<T>): T {
        if (modelClass.isAssignableFrom(FourDigitViewModel::class.java)) {
            @Suppress("UNCHECKED_CAST")
            return FourDigitViewModel(repository) as T
        }
        throw IllegalArgumentException("Unknown ViewModel class")
    }
}