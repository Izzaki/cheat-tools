The easiest way to display scrapped data in live mode. 
Usefull to check some informations like characters list, rankings etc.

Due to CORS policy it has to be opened with disabled security in browser.
	start chrome --disable-web-security --user-data-dir=%temp% *PATH*/index.html

Sweet alias:

	doskey chromex = start chrome --disable-web-security --user-data-dir=%temp% $*

then

	chromex *PATH*/index.html
