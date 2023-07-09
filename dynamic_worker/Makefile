MODULE_big = my_dynamic_bgw

OBJS = my_dynamic_bgw.o

EXTENSION = my_dynamic_bgw

DATA = my_dynamic_bgw--1.0.sql

ifdef USE_PGXS
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) —pgxs)
include $(PGXS)
else
subdir = contrib/my_dynamic_bgw
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif
create function my_dynamic_bgw() returns void AS 'MODULE_PATHNAME', 'my_dynamic_bgw' LANGUAGE C;