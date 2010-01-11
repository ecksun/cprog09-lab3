#include "exit.h"
#include "environment.h"
#include <sstream>

#include <iostream>

namespace da_game {

    int Exit::instances;
    /**
     * Creates a new exit with some default parameters, but without
     * any outfall. This is probably useless unless an outfall is
     * later set.
     */
    Exit::Exit() : id(instances++), description(""), has_lock(false), key_code(""), locked(false) {
    }

    /**
     * Constructs a new exit with the given outfall and description.
     *
     * Notice: All parameters except outfall are given default values
     * if not specified.
     *
     * @param outfall Where this exit leads to
     * @param has_lock Whether or not this exit has a lock
     * @param key_code The key code for this exit
     * @param locked The locked state of this exit
     * @param description A short description of this exit
     */
    Exit::Exit(Environment * outfall, bool has_lock, std::string key_code, bool locked, std::string description) 
        : id(instances++), outfall(outfall), description(description), has_lock(has_lock), key_code(key_code), locked(locked) {
    }

    /**
     * Returns the outfall of this exit, that is, where it leads to.
     *
     * @return The outfall
     */
    Environment * Exit::get_outfall() const {
        return outfall;
    }

    /**
     * Returns whether or not this exit is locked.
     *
     * @return true if locked, false otherwise
     */
    bool Exit::is_locked() {
        return this->locked;
    }

    /**
     * Sets what environment this exit leads to.
     *
     * @param outfall The new environment this exit should lead to
     */
    void Exit::set_outfall(Environment * outfall) {
        this->outfall = outfall;
    }
    
    /**
     * Sets the description of this exit to the one specified.
     *
     * @param description The new description
     */
    void Exit::set_description(std::string description) {
        this->description = description;
    }

    /**
     * Sets this exit's key code that is required in order to unlock
     * it.
     *
     * @param key_code The new key code
     */
    void Exit::set_key_code(std::string key_code) {
        this->key_code = key_code;
    }

    /**
     * Sets the locked state of this exit.
     *
     * @param locked Whether or not this exit is locked
     */
    void Exit::set_locked(bool locked) {
        this->locked = locked;
    }

    /**
     * Locks this exit iff it has a lock and the key code from the 
     * specified key agrees to the one of this exit.
     *
     * @param key The key to lock with
     * @return The new locked state of this exit
     */
    bool Exit::lock(Key * key) {
        if (!this->has_lock) {
            return this->locked;
        }

        if (key->get_key_code() == this->key_code) {
            this->locked = true;
            std::cerr << "Locked exit" << std::endl;
        }

        return this->locked;
    }

    /**
     * Unlocks this exit iff this exit has a lock and the key code 
     * of the specified key equals the one of this exit.
     *
     * @param key The key to unlock with
     * @return The new locked state of this exit
     */
    bool Exit::unlock(Key * key) {
        if (!this->has_lock) {
            return this->locked;
        }

        if (key->get_key_code() == this->key_code) {
            this->locked = false;
            std::cerr << "Unlocked exit" << std::endl;
        }

        return this->locked;
    }

    /**
     * Toggles the status of this exit's lock; if it is locked it gets
     * unlocked and vice versa. However, this does only work if the 
     * correct key is provided.
     *
     * @param key The key to lock/unlock with
     * @return The new locked status of this exit
     */
    bool Exit::toggle_lock(Key * key) {
        if (is_locked()) {
            return unlock(key);
        } else {
            return lock(key);
        }
    }

    void Exit::save(std::fstream & save, std::string env_description) {
        save << "EXI" << id;
        save << ":ENV" << outfall->id;
        save << ":has_lock=" << has_lock;
        save << ",key_code=" << key_code;
        save << ",locked=";
        if (locked)
            save << "true";
        else
            save << "false";
        save << ",description=" << description;
        save << ",env_desc=" << env_description;
        save << std::endl;

    }

    Exit * Exit::load(std::string line, const std::map<std::string, Environment *> & envs) {

        line = line.substr(line.find_first_of(':')+1);
        std::string tmp;
        tmp = line.substr(0,line.find_first_of(':'));
        tmp = tmp.substr(3);
        std::string envID = tmp;

        // std::istringstream iss(tmp);
        // int envID;
        // iss >> envID;

        line = line.substr(line.find_first_of(':')+1);

        tmp = line.substr(9);
        tmp = tmp.substr(0,1);

        bool has_lock = false;
        if (tmp == "1")
            has_lock = true;

        line = line.substr(line.find_first_of(',')+1);

        tmp = line.substr(9);
        tmp = tmp.substr(0,tmp.find_first_of(','));

        std::string key_code = tmp;


        line = line.substr(line.find_first_of(',')+1);

        tmp = line.substr(7);
        tmp = tmp.substr(0,tmp.find_first_of(','));

        bool locked = false;
        if (tmp == "true")
            locked = true;

        line = line.substr(line.find_first_of(',')+1);

        std::string description = line.substr(12);
        description = description.substr(0,description.find_first_of(','));

        line = line.substr(line.find_first_of(',')+1);

        std::string env_desc = line.substr(9);

        Exit * exit = new Exit(envs.find(envID)->second, has_lock, key_code, locked, description);
        return exit;
        
    }

}
