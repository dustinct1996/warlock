class IDGenerator {
public:
    uint32_t getNewID() {
        return id++;
    }
private:
    uint32_t id = 0;
};