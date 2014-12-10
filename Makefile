MAKE = make

all: engine

clean: engine_clean

engine:
	$(MAKE) -C src/engine
	
engine_clean:
	$(MAKE) -C src/engine clean

install: uninstall webdir
	cp -r src/* /var/www/html/gpct && chmod -R a+rw /var/www/html/gpct
	
uninstall:
	rm -rf /var/www/html/*

webdir:
	mkdir -p /var/www/html/gpct
