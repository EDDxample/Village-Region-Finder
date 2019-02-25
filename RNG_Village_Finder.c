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

    // removeDeadAndOutOfRangeDoors
    nextInt(&seed, 50);

    // spawnGolems
    if (nextInt(&seed, 7000) == 0)
    {

        // Golem coords
        int golemX = nextIntP2(&seed, 16) - 8;
        int golemY = nextInt(&seed, 6) - 3;
        int golemZ = nextIntP2(&seed, 16) - 8;

        // Block coords
        int fromX = x * 1280;
        int fromZ = z * 1280;
        int toX = fromX + 1280;
        int toZ = fromZ + 1280;

        printf("from %d %d to %d %d; %d %d %d\n", fromX, fromZ, toX, toZ, golemX, golemY, golemZ);
        stop = true;
    }
}

void seedloop()
{
    int x = 0;
    int z = 0;
    int di = 1;
    int dj = 0;
    int segmentLength = 1;
    int segmentPassed = 0;
    while ((x < radius) && (!stop))
    {
        seed = 544LL;
        findAt(x, z);
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