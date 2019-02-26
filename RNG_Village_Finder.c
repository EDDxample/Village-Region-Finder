#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "javaRNG.h"

bool stop;
const int radius = 23437;
int64_t seed = 544LL;

void findAt(int x, int z)
{
    // canSpawnStructureAtCoords
    setSeedMC(&seed, x, z);
    nextIntLoop(&seed, 60, 4); // 4x nextInt(60)

    // playerCheckLight
    int totalPlayers = 1;
    nextInt(&seed, totalPlayers);
    nextIntLoop(&seed, 11, 3); // 3x nextInt(11)

    // updateBlocks
    int renderDistance = 3;
    int rdSide = renderDistance * 2 + 1;
    nextIntLoopP2(&seed, rdSide * rdSide); // (2n+1)^2 x nextInt(16)

    /* ===== PER VILLAGE ===== */
    int minGolems = 10;

    int golemCounter = 0;
    int villageCounter = 0;

    while (golemCounter <= minGolems && villageCounter <= 4000)
    {
        ++villageCounter;
        // removeDeadAndOutOfRangeDoors
        nextInt(&seed, 50);

        // spawnGolems
        if (nextInt(&seed, 7000) == 0)
        {
            ++golemCounter;
            nextIntP2(&seed, 16);
            nextInt(&seed, 6);
            nextIntP2(&seed, 16);
        }
    }

    if (villageCounter <= 4000)
        printf("region: %d %d; %d villages\n", x, z, villageCounter);
    if (villageCounter <= 1000)
        stop = true;
}

void seedloop()
{
    int x = 0;
    int z = 0;
    int di = 1;
    int dj = 0;
    int segmentLength = 1;
    int segmentPassed = 0;
    long long regionCounter = 0;

    while ((x < radius) && (!stop))
    {
        seed = 544LL;
        findAt(x, z);

        ++regionCounter;
        if (regionCounter % 100000 == 0)
            printf("%d regions...\n", regionCounter);

        x += di;
        z += dj;

        segmentPassed++;
        if (segmentPassed == segmentLength)
        {
            segmentPassed = 0;

            int buffer = di;
            di = -dj;
            dj = buffer;
            if (dj == 0)
            {
                segmentLength++;
            }
        }
    }
}

int main() { seedloop(); }