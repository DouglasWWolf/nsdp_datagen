#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <set>

using namespace std;

const uint32_t SEMIPHASE_SIZE = 0x200000;
const int      FRAME_COUNT    = 100;
const char*    FILENAME       = "nsdp_dataset.bin";

//=============================================================================
// psuedo_prbs() - This is a cheesy way to generate a long sequence of 32-bit
//                 values that don't repeat for hundreds of millions of 
//                 entries.
//=============================================================================
uint32_t psuedo_prbs(uint32_t seed)
{
    seed += 2718281823;     
    seed ^= 0xAAAAAAAA;
    return seed;
}
//=============================================================================


//=============================================================================
// execute() - Writes a bunch of semi-phases to an output file
//=============================================================================
void execute()
{
    // This is the seed value into our psuedo-PRBS generator
    uint32_t seed = 3141592653;
        
    // Create the output file
    FILE* ofile = fopen(FILENAME, "w");
    if (ofile == nullptr)
    {
        fprintf(stderr, "Can't create %s\n", FILENAME);
        exit(1);
    }

    // A single semi-phase consists of this many 32-bit words
    const uint32_t WORD_COUNT = SEMIPHASE_SIZE / sizeof(uint32_t);

    // Allocate enough RAM to hold a semi-phase full of data
    uint32_t* buffer = new uint32_t[WORD_COUNT];

    // We're going to write a bunch of semi-phases to the file
    for (int i=0; i<FRAME_COUNT; ++i)
    {
        // Get the next value from our psuedo-PRBS generator
        seed = psuedo_prbs(seed);

        // Fill this semi-phase with our psuedo-PRBS value
        for (uint32_t idx=0; idx<WORD_COUNT; ++idx) buffer[idx] = seed;

        // Write this semi-phase to our output file
        fwrite(buffer, SEMIPHASE_SIZE, 1, ofile);
    }

    // Close the output file, we're done
    fclose(ofile);
}
//=============================================================================


//=============================================================================
// main() - Execution begins here
//=============================================================================
int main()
{
    execute();
}
//=============================================================================
