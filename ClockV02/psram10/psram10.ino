int n_elements = 1000;

void setup(){
        Serial.begin(115200);
        //Init
        if(psramInit()){
        Serial.println("\nPSRAM is correctly initialized");
        }else{
        Serial.println("PSRAM not available");
        }

        //Create an array of n_elements
        int available_PSRAM_size = ESP.getFreePsram();
        Serial.println((String)"PSRAM Size available (bytes): " + available_PSRAM_size);

        int *array_int = (int *) ps_malloc(n_elements * sizeof(int)); //Create an integer array of n_elements
        array_int[0] = 42;
        array_int[999] = 42; //We access array values like classic array

        int available_PSRAM_size_after = ESP.getFreePsram();
        Serial.println((String)"PSRAM Size available (bytes): " + available_PSRAM_size_after); // Free memory space has decreased
        int array_size = available_PSRAM_size - available_PSRAM_size_after;
        Serial.println((String)"Array size in PSRAM in bytes: " + array_size);

        //Delete array
        free(array_int); //The allocated memory is freed.
        Serial.println((String)"PSRAM Size available (bytes): " +ESP.getFreePsram());
}

void loop() {
}