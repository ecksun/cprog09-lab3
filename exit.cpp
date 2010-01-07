#include "exit.h"

#include <iostream>

namespace da_game {

    /**
     * Creates a new exit with some default parameters, but without
     * any outfall. This is probably useless unless an outfall is
     * later set.
     */
    Exit::Exit() : description(""), has_lock(false), key_code(""), locked(false) {
    }

    /**
     * Constructs a new exit with the given outfall and description.
     *
     * Notice: All parameters except outfall are given default values
     * if not specified.
     *
     * @param outfall Where this exit leads to
     * @param description A short description of this exit
     * @param has_lock Whether or not this exit has a lock
     * @param key_code The key code for this exit
     * @param locked The locked state of this exit
     */
    Exit::Exit(Environment * outfall, std::string description, 
            bool has_lock, std::string key_code, bool locked) 
        : outfall(outfall), description(description), has_lock(has_lock), key_code(key_code), locked(locked) {
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

}
