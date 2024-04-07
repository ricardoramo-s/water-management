#ifndef WATER_MANAGEMENT_PIPE_H
#define WATER_MANAGEMENT_PIPE_H


#include <string>
#include <unordered_map>
#include <vector>


#include "City.h"
#include "Pump.h"
#include "Reservoir.h"

class Pipe {

private:

    /**
     * @brief Struct for custom hash function for pairs.
     *
     * This struct defines a custom hash function for pairs of strings.
     * It's used by the PipesMap to calculate the hash of the keys.
     */
    struct hash_pair {
        /**
         * @brief Calculates the hash value of a pair of strings.
         *
         * @param p The pair of strings.
         * @return The hash value of the pair.
         */
        size_t operator()(const std::pair<std::string, std::string>& p) const
        {
            auto hash1 = std::hash<std::string>{}(p.first);
            auto hash2 = std::hash<std::string>{}(p.second);

            if (hash1 != hash2) {
                return hash1 ^ hash2;
            }

            return hash1;
        }
    };

public:

    /**
     * @brief Key type used in the PipesMap.
     */
    typedef std::pair<std::string, std::string> Key;
    /**
     * @brief Map type mapping keys to Pipe pointers.
     */
    typedef std::unordered_map<Key, Pipe*, hash_pair> PipesMap; //org->dest : pipe

    /**
     * @brief Struct for storing multiple PipesMaps.
     */
    struct PipesMultiMap {

    public:

        /**
         * @brief not implemented
         */
        Pipe *getPipe(Key key, int &n);

        /**
         * @brief Adds a reservoir-to-pump pipe to the map.
         *
         * @param pipe The pipe to add.
         * @return True if the pipe was added successfully, false otherwise.
         */
        bool addRtPPipe(Pipe *);

        /**
         * @brief Adds a pump-to-pump pipe to the map.
         *
         * @param pipe The pipe to add.
         * @return True if the pipe was added successfully, false otherwise.
         */
        bool addPtPPipe(Pipe *);

        /**
         * @brief Adds a pump-to-city pipe to the map.
         *
         * @param pipe The pipe to add.
         * @return True if the pipe was added successfully, false otherwise.
         */
        bool addPtCPipe(Pipe *);

        /**
         * @brief Gets the reservoir-to-pump map.
         *
         * @return The reservoir-to-pump map.
         */
        PipesMap getRtPMAP();

        /**
         * @brief Gets the pump-to-pump map.
         *
         * @return The pump-to-pump map.
         */
        PipesMap getPtPMAP();

        /**
         * @brief Gets the pump-to-city map.
         *
         * @return The pump-to-city map.
         */
        PipesMap getPtCMAP();

    private:

        /**
         * @brief Map for reservoir-to-pump pipes.
         */
        PipesMap RtPMap;

        /**
         * @brief Map for pump-to-pump pipes.
         */
        PipesMap PtPMap;

        /**
         * @brief Map for pump-to-city pipes.
         */
        PipesMap PtCMap;
    };


    /**
     * @brief Default constructor.
     */
    Pipe() = default;

    /**
     * @brief Constructor with parameters.
     *
     * @param org The origin of the pipe.
     * @param dest The destination of the pipe.
     * @param capacity The capacity of the pipe.
     * @param direction The direction of the pipe (1 for directed, 0 for undirected).
     */
    Pipe(std::string org, std::string dest, int capacity, bool direction);

    /**
     * @brief not implemented.
     */
    ~Pipe();

    /**
     * @brief Gets the origin of the pipe.
     *
     * @return The origin of the pipe.
     */
    std::string getOrg() const;

    /**
     * @brief Gets the destination of the pipe.
     *
     * @return The destination of the pipe.
     */
    std::string getDest() const;

    /**
     * @brief Gets the capacity of the pipe.
     *
     * @return The capacity of the pipe.
     */
    int getCapacity() const;

    /**
     * @brief Gets the direction of the pipe.
     *
     * @return The direction of the pipe (1 for directed, 0 for undirected).
     */
    bool getDirection() const;

    /**
     * @brief Adds a pipe to the static PipesMultiMap.
     *
     * @param pipe The pipe to add.
     * @return True if the pipe was added successfully, false otherwise.
     * @complexity O(1)
     */
    static bool addPipe(Pipe* pipe);

    /**
     * @brief Gets a pipe from the static PipesMultiMap based on its key.
     *
     * @param key The key of the pipe.
     * @return The pipe associated with the key, or nullptr if not found.
     * @complexity O(1)
     */
    static Pipe* getPipe(Key key);

    /**
     * @brief Gets the static PipesMultiMap.
     *
     * @return The static PipesMultiMap.
     */
    static PipesMultiMap getPipesMultiMap();

private:

    /**
     * @brief Generates a key for a pipe.
     *
     * @param pipe The pipe for which to generate the key.
     * @return The key generated for the pipe.
     */
    static Key makeKey(Pipe* pipe);

    /**
     * @brief Selects the map to use based on the key.
     *
     * @param key The key to determine the map.
     * @param n Output parameter indicating the map index (0 for RtP, 1 for PtP, 2 for PtC).
     * @return True if the map was successfully selected, false otherwise.
     * @complexity O(1)
     */
    static bool selectMap(Key key, int& n);

    /**
     * @brief The origin of the pipe.
     */
    std::string org;

    /**
     * @brief The destination of the pipe.
     */
    std::string dest;

    /**
     * @brief The capacity of the pipe.
     */
    int capacity;

    /**
     * @brief The direction of the pipe (1 for directed, 0 for undirected).
     */
    bool direction;

    /**
     * @brief Static PipesMultiMap storing all pipes.
     */
    static PipesMultiMap pipesMultiMap;
};


#endif //WATER_MANAGEMENT_PIPE_H
