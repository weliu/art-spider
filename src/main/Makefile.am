bin_PROGRAMS=art_spider
art_spider_SOURCES=main.cpp
art_spider_LDADD=$(top_srcdir)/src/lib/liblog.a \
				$(top_srcdir)/src/lib/libcurlhtml.a \
				$(top_srcdir)/src/lib/libmyconf.a
art_spider_LDFLAGS=-L/usr/local/lib
INCLUDES=-I$(top_srcdir)/src/include -I/usr/local/include
LIBS=-lcurl -llog4cplus -lpthread

