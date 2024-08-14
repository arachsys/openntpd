BINDIR = $(PREFIX)/bin

CONFFILE = /etc/ntpd.conf
CTLSOCKET = /run/ntpd.sock
DRIFTFILE = /var/lib/ntpd.drift
USERNAME = ntp

CFLAGS = -O2 -Wall
LIBS = -ltls -lm

COMPAT != uname -s | tr A-Z a-z
CCFLAGS = $(CFLAGS) $(LDFLAGS) -I$(COMPAT) -Isrc -D_GNU_SOURCE

CCFLAGS += -DCONFFILE=\"$(CONFFILE)\"
CCFLAGS += -DCTLSOCKET=\"$(CTLSOCKET)\"
CCFLAGS += -DDRIFTFILE=\"$(DRIFTFILE)\"
CCFLAGS += -DNTPD_USER=\"$(USERNAME)\"

all: ntpd

clean:
	rm -f ntpd src/parse.c

ntpd: src/*.[ch] src/parse.c $(COMPAT)/*.[ch] Makefile
	$(CC) $(CCFLAGS) -o ntpd src/*.c $(COMPAT)/*.c $(LIBS)

src/parse.c: src/parse.y Makefile
	$(YACC) -o src/parse.c src/parse.y

install: ntpd
	mkdir -p $(DESTDIR)$(BINDIR)
	install -s ntpd $(DESTDIR)$(BINDIR)
	ln -f $(DESTDIR)$(BINDIR)/{ntpd,ntpq}
	if test -n "$(MANDIR)"; then \
	  mkdir -p $(DESTDIR)$(MANDIR)/{man5,man8}; \
	  install -m 0644 man/*.5 $(DESTDIR)$(MANDIR)/man5; \
	  install -m 0644 man/*.8 $(DESTDIR)$(MANDIR)/man8; \
	fi

.PHONY: all clean install
