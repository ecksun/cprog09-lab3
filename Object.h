namespace da_game {
    class Object {
        int weight;
        public:
        virtual int weight() = 0;
        virtual int volume() = 0;
        virtual int price() = 0;
    };
}
