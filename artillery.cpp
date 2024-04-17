#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cmath>

using namespace std;

const int kNumShells = 30;      // allowed 30 shells per target (given)
const int kMinDist = 300;       // min distance for a target
const int kMaxDist = 900;       // max distance for a target
const double kVelocity = 200.0; // initial velocity of 200 ft/sec (given)
const double kGravity = 32.2;   // gravity for distance calculation (given)
const double kPi = 3.1415;      // value of pi

int distanceCalc(double in_angle)
{
    // The following calculates how far the shot goes given its angle of projection, velocity, and how long it stays in the air.
    double time_in_air;
    time_in_air = (2.0 * kVelocity * sin(in_angle)) / kGravity;
    return (int)round((kVelocity * cos(in_angle)) * time_in_air);
}

int CheckShot()
{
    double distance;
    double angle;
    cout << "Firing at an angle of degree : ";
    if (!(cin >> angle))
        return -1;

    // convert to radians
    angle = (angle * kPi) / 180;
    distance = distanceCalc(angle);
    return distance;
}

// generate random position for enemy

int target()
{
    int enemy_position;
    int t = time(NULL);
    srand(t);
    enemy_position = rand() % kMaxDist + kMinDist;
    cout << "The enemy is " << enemy_position << " feet away" << endl;
    return enemy_position;
}
int fiRe(int num_killed)
{
    int enemy, shots, distance, hit;
    shots = kNumShells;
    enemy = target();
    distance = 0;
    hit = 0;
    do
    {
        distance = CheckShot();
        if (distance == -1)
        {
            cout << "enter numbers only" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (abs(enemy - distance) <= 1)
        {
            hit = 1;
            num_killed++;
            cout << "--TARGET ELIMINATED--" << endl;
            cout << "it took you " << kNumShells - shots + 1 << "shots." << endl;
            cout << "you eliminated " << num_killed << " enemies." << endl;
        }
        else
        {
            shots--;
            if (distance > enemy)
            {
                cout << "--MISSED--" << endl;
                cout << "you over shot by " << abs(enemy - distance) << endl;
            }
            else
            {
                cout << "--MISSED--" << endl;
                cout << "you under shot by " << abs(enemy - distance) << endl;
            }
        }

    } while ((shots > 0) && (!(hit)));
    if (shots == 0)
    {
        cout << "you've run out of ammo" << endl;
        return num_killed;
    }
}

// startup text
void start_up()
{
    cout << "Welcome to Artillery." << endl;
    cout << "You are in the middle of a war and being charged by thousands of enemies." << endl;
    cout << "You have one cannon, which you can shoot at any angle." << endl;
    cout << "You have " << kNumShells << " cannonballs per target." << endl;
    cout << "Let's begin..." << endl;
}

int main()
{
    start_up();
    int killed = 0;
    char done;
    do
    {
        killed = fiRe(killed);
        cout << "Enemy Spotted..Approach? (y/n) " << endl;
        cin >> done;
    } while (done != 'n');
    cout << "you killed" << killed << "of the enemy." << endl;

    return 0;
}
