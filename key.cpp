#include "key.h"

namespace da_game {

    /**
     * Creates a new key with the given key code.
     * 
     * @param key_code The key code for this key
     */
    Key::Key(std::string key_code) : key_code(key_code) {
        
    }

    /**
     * Returns the weight of this key.
     *
     * @return the weight
     */
    int Key::weight() const {
        return 1;
    }

    /**
     * Returns the volume of this key.
     *
     * @return the volume
     */
    int Key::volume() const {
        return 1;
    }

    /**
     * Returns the price of this key.
     *
     * @return the price
     */
    int Key::price() const {
        return 50;
    }

    /**
     * Returns the type of this key.
     *
     * @return the type
     */
    std::string Key::type() const {
        return "Key";
    }

    /**
     * Returns the key code of this key.
     *
     * @return the key code
     */
    std::string Key::get_key_code() const {
        return this->key_code;
    }

    /**
     * Compares the specified object to this key and returns true if 
     * they are considered equal. In this case they are considered 
     * equal if and only if the specified object is also a key and
     * all of its parameters coincide with the ones of this key.
     *
     * @return true iff the object is identically equal to this key
     */
    bool Key::operator==(Key & key) const {
        return  object.weight() != this->weight() ||
                object.volume() != this->volume() ||
                object.price() != this->price() || 
                object.type() != this->type();
    }

}
