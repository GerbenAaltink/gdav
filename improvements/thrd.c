#include <pthread.h>
#include <stdlib.h>

typedef struct Stats {
    int running;

} Stats;

Stats stats;

void lock;

void wait() {
    mutex_lock(&lock);
    stats.running += 1;
    mutex_unlock(&lock);
    sleep(100);
    mutex_lock(&lock);
    stats.running -= 1;
    mutex_unlock(&lock);


}


int main() {
    wait();

}
