plugin_LTLIBRARIES = \
	libdummy.la

libdummy_la_SOURCES = 		\
	msd-dummy-manager.c	\
	msd-dummy-manager.h	\
	msd-dummy-plugin.c	\
	msd-dummy-plugin.h

libdummy_la_CPPFLAGS = \
	-I$(top_srcdir)/gde2-settings-daemon		\
	-DGDE2_SETTINGS_LOCALEDIR=\""$(datadir)/locale"\" \
	$(AM_CPPFLAGS)

libdummy_la_CFLAGS = \
	$(SETTINGS_PLUGIN_CFLAGS)	\
	$(AM_CFLAGS)

libdummy_la_LDFLAGS = 		\
	$(MSD_PLUGIN_LDFLAGS)

libdummy_la_LIBADD  = 		\
	$(SETTINGS_PLUGIN_LIBS)

plugin_in_files = 		\
	dummy.gde2-settings-plugin.in

plugin_DATA = $(plugin_in_files:.gde2-settings-plugin.in=.gde2-settings-plugin)

EXTRA_DIST = 			\
	$(plugin_in_files)

CLEANFILES = 			\
	$(plugin_DATA)

DISTCLEANFILES =		\
	$(plugin_DATA)

@MSD_INTLTOOL_PLUGIN_RULE@

# override to _not_ install the test plugin
# do not copy into your plugin
install-pluginDATA:
install-pluginLTLIBRARIES:
