plugin_LTLIBRARIES = \
	libsmartcard.la

libsmartcard_la_SOURCES = \
	msd-smartcard-plugin.h  \
	msd-smartcard-plugin.c  \
	msd-smartcard.h         \
	msd-smartcard.c         \
	msd-smartcard-manager.h \
	msd-smartcard-manager.c

libsmartcard_la_CPPFLAGS = \
	-I$(top_srcdir)/gde2-settings-daemon \
	-DGDE2_SETTINGS_LOCALEDIR=\""$(datadir)/locale"\" \
	-DSYSCONFDIR=\""$(sysconfdir)"\" \
	-DLIBDIR=\""$(libdir)"\" \
	-DMSD_SMARTCARD_MANAGER_NSS_DB=\""$(NSS_DATABASE)"\" \
	$(AM_CPPFLAGS)

libsmartcard_la_CFLAGS = \
	$(SETTINGS_PLUGIN_CFLAGS) \
	$(GDE2_CFLAGS)	\
	$(NSS_CFLAGS)	\
	$(AM_CFLAGS)

libsmartcard_la_LDFLAGS = \
	$(MSD_PLUGIN_LDFLAGS)

libsmartcard_la_LIBADD = \
	$(SETTINGS_PLUGIN_LIBS)	\
	$(NSS_LIBS)

@MSD_INTLTOOL_PLUGIN_RULE@

plugin_in_files = \
	smartcard.gde2-settings-plugin.in

plugin_DATA = $(plugin_in_files:.gde2-settings-plugin.in=.gde2-settings-plugin)

EXTRA_DIST = \
	$(plugin_in_files)

CLEANFILES = \
	$(plugin_DATA)

DISTCLEANFILES = \
	$(plugin_DATA)
