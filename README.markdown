# cprog09: Laboration 3 

Uppgiften går ut på att skriva ett lite större program med hjälp av arv,
polymorfi och standardklasserna (STL).

## TODO

* Alla .o filer borde hamna i en egen mapp så det inte blir så stökigt
* Använd medlemspekare istället för statiska funktionspekare
* Förslag: Låt varje environment innehålla en lista över Exit-objekt, där
  ett Exit-objekt innehåller typ "direction", "new_environment*", "locked", 
  "symmetric_lock" och "unlocking_item". Kanske även någon liten beskrivning
  av utgången och ett eventuellt lås. På det här viset kan vi implementera
  icke-symmetriska lås, t.ex. dörrar som gått i baklås. Dessutom tror jag det
  blir lättare att hålla rätt på pekarna, jämfört med att varje Exit ska
  innehålla ett par av utgångar. Moment 22-problemet kvarstår dock med 
  instansiering av Environments; för att skapa en miljö med utgångar måste
  man först ha skapat en annan miljö. Det kan dock lösas genom att först
  skapa miljöerna och sedan lägga till utgångar genom add_exit eller dylikt.
* Funkar det med private på instances i Object och Actor?
* Stoppa in player i environmenten han är i 




## Markdown syntax

http://daringfireball.net/projects/markdown/syntax
