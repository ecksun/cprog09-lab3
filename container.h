namespace da_game {
    class container : public Object  {
        public:
            virtual int hold_weight() = 0;
            virtual int hold_volume() = 0;
            virtual int add(Object) = 0;
            virtual int remove(Object) = 0;
    };
}

