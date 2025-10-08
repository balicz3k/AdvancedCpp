#include "DataSharing.hpp"
#include "DeadLock.hpp"
#include "LiveLock.hpp"
#include <limits>

int main()
{
    DeadLock dl;
    // dl.demo();
    LiveLock ll;
    // ll.demo(5000);
    DataSharing::dataSharedAsReferenceDemo();
    DataSharing::dataSharedByFuturePromise();
}