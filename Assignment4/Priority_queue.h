// Priority_queue.h

class Priority_queue {
public:
    // C++ base classes should always provide a virtual destructor so that
    // deriving classes can over-ride if they need to.
    virtual ~Priority_queue() { }

    // Pre-condition:
    //    none
    // Post-condition:
    //    Returns true if there are 0 items in this priority queue.
    virtual bool empty() const = 0;

    // Pre-condition:
    //    none
    // Post-condition:
    //    Puts x into this priority queue. If x is already in the priority
    //    queue, then nothing is added (i.e. duplicates are not allowed).
    virtual void insert(int x) = 0;

    // Pre-condition:
    //    !empty()
    // Post-condition:
    //    Removes and returns the smallest element from this priority queue.
    virtual int pop_min() = 0;

}; // class Priority_queue