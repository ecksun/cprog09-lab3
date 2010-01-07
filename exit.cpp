#include "exit.h"

namespace da_game {

    /**
     * Creates a new exit with some default parameters.
     */
    Exit::Exit() : description(""), key_code(""), locked(false), lockable(false) {
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
     * Locks this exit iff it is lockable and the key code from the 
     * specified key agrees to the one of this exit.
     *
     * @param key The key to lock with
     * @return The new locked state of this exit
     */
    bool Exit::lock(Key * key) {
        if (!this->lockable) {
            return this->locked;
        }

        if (key->get_key_code() == this->key_code) {
            this->locked = true;
        }

        return this->locked;
    }

    /**
     * Unlocks this exit iff this exit is lockable and the key code 
     * of the specified key equals the one of this exit.
     *
     * @param key The key to unlock with
     * @return The new locked state of this exit
     */
    bool Exit::unlock(Key * key) {
        if (!this->lockable) {
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
