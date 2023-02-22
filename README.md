# Aufgabenstellung

Schreiben Sie eine Ringspeicherbiblithek ringbuf.c in C. Dieser Ringspeicher soll die Zeichen der hinzugefügten Strings ohne Teminator=Symbol zusammenhängend abspeichern. Dafür soll die Bibliothek das Folgende bereitstellen:

- einen ringbuf_t Datentyp,

- eine Funktion ringbuf_t* ringbuf_create(size_t size), welche einen Ringspeicher allokiert, der size Charakter halten kann,

- eine Funktion void ringbuf_delete(ringbuf_t *buf) zum Freigeben der Datenstruktur,

- eine Funktion int ringbuf_append(ringbuf_t *buf, char *data, size_t size) zum Anhängen von size Buchstaben aus data (sollte der Ringspeicher zu klein sein, soll ein geeigneter Fehlerwert zurückgegeben werden),

- eine Funktion int ringbuf_pop(ringbuf_t *buf, size_t size, char *target) zum Lesen und Entfernen von size Buchstaben aus den Ringspeicher in den target String,

- eine Funktion int ringbuf_pop_delimited(ringbuf_t *buf, char d, char *target, size_t target_size) zum Lesen von Buchstaben bis zum Trennzeichen d in den target String, der target_size groß ist.

Schreiben Sie darüber hinaus ein Programm prog.c, welches diese Bibliothek nutzt. Dieses soll einen oder mehrere Sätze, welche per Kommandozeilenargumente an das Programm übergeben werden, wortweise in den Ringspeicher speichern. Benutzen Sie dazu argc und argv. Außerdem soll es den ersten Satz wieder ausgeben.

Erstellen Sie ein Makefile, das bei Aufruf von make aus ringbuf.c eine statische Bibliothek und aus prog.c ein Programm erstellt. Verwenden Sie beim Kompilieren die Compiler-Optionen -Wall, Wextra und -pedantic!

Ihre Bibliothek und Ihr Programm muss mögliche Fehler abfangen. Außerdem soll Ihr Programm passende Fehlermeldungen via stderr ausgeben. Achten Sie außerdem darauf, dass in Ihren Funktionen keine Buffer-Overflows auftreten können.
