namespace da_game {
    class envoirement {
        /*
         * returnera beskrivning av vad miljönnehåer, vilka
         * föåman kan ta och vilka aktö som befinner sig pålatsen.
         */
        virtual std::string description() = 0;
        /*
         * returnera vilka utgåar som finns
         */
        virtual std::vector<std::string> directions() = 0;
        /*
         * returnera granne (t.ex. referens till objekt) i gi-
         * ven riktning
         */
        virtual envoirement neighbor(std::string) = 0;
        /*
         * enter(Character) - aktöommer till platsen
         */
        virtual void enter(Actor) = 0;
        /*
         * leave(Character) - aktöåfråplatsen
         */
        virtual void leave(Actor) = 0;
        /*
         * pick_up(Object) - nån tar upp ett föåsom finns pålatsen
         */
        virtual bool pick_up(Object) = 0;
        /*
         * drop(Object) - nån läer ner ett föåpålatsen
         */
        virtual void drop(Object) = 0;
    };
}
