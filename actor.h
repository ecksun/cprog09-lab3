namespace da_game {
    class actor {
        int hp;
        public:
        void run();
        virtual std::string type() = 0;
        virtual std::string name() = 0;
        virtual void go(Direction) = 0;
        virtual void fight(Character) = 0;
        virtual void pick_up(Object) = 0;
        virtual void drop(Object) = 0;
        virtual void talk_to(Character) = 0;
    };
}
