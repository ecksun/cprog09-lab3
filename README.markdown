# cprog09: Laboration 3 #

Uppgiften går ut på att skriva ett lite större program med hjälp av arv,
polymorfi och standardklasserna (STL).

## TODO ##

* Alla .o filer borde hamna i en egen mapp så det inte blir så stökigt
* Använd medlemspekare istället för statiska funktionspekare
* <del>Förslag: Låt varje environment innehålla en lista över Exit-objekt, där
  ett Exit-objekt innehåller typ "direction", "new_environment*", "locked", 
  "symmetric_lock" och "unlocking_item". Kanske även någon liten beskrivning
  av utgången och ett eventuellt lås. På det här viset kan vi implementera
  icke-symmetriska lås, t.ex. dörrar som gått i baklås. Dessutom tror jag det
  blir lättare att hålla rätt på pekarna, jämfört med att varje Exit ska
  innehålla ett par av utgångar. Moment 22-problemet kvarstår dock med 
  instansiering av Environments; för att skapa en miljö med utgångar måste
  man först ha skapat en annan miljö. Det kan dock lösas genom att först
  skapa miljöerna och sedan lägga till utgångar genom add_exit eller dylikt. 
      Låter finfint :)</del> DONE
* <del>Funkar det med private på instances i Object och Actor?</del>
* <del>Stoppa in player i environmenten han är i</del> DONE
* Storyn kan vara som starwars, man är anakin osv
  * Så målet med spelet är att bara slakta alla som finns, som anakin gör i jedi-templet i Episode III
* Ett förslag är att när det händer saker i ett rum så är det någon "global" metod som hanterar vad som händer, så man kan dissa det om det händer saker i ett rum som man inte är i
* Diskutera format på sparfiler samt kartor (3.2 och 3.3)
* <del>En fight  kan instansiera en speciell miljö utan exits, så registrerar man samtidigt ett nytt kommando till terminalen som kan vara typ "fight" (så man kan välja vapen osv)</del>
* Låta Inside ta emot Environments-pekare som tidigare och automatiskt skapa standard-exits till dessa.
* Se över Environment::description(). Skriva till stdout eller returnera sträng?
* <del>Fixa låsmekanismen på Exits.</del>
* Skapa PairExit som returnerar olika get_outfall beroende på vilket av de två rummen man står i, o.s.v.
* Se över Segmentation Fault när man dör.
* Se till så man måste läsa upp en dörr för att komma till evil lair (för att behöva använda nyckel för att klara spelet, light saber får INTE ligga i det låsta rummet :D)
* stringtoint() måste hantera fel



## Rules to conform to ##

### Objects ###

Objects should always be owned by exactly one of the following.

* An Environment 
* A Container
* An Actor

In that way it is easier to make sure no objects are causing memory leaks or
unexpected null references. We are thereby implementing the ownership semantics
from auto_ptr; there is always exactly one object owning another object. If an
object is to be deleted, only the owning object is allowed to do that and is
also responsible for removing the pointer to that object.



# Markdown syntax

http://daringfireball.net/projects/markdown/syntax
