 # Maintainer: torvic
 # Creator: Leinnan

 pkgname=('i3gs')
 pkgver=1.0.0
 pkgrel=1
 arch=('i686' 'x86_64')
 url="https://github.com/Leinnan/i3gs"
 pkgdesc="i3 status bar for i3-gaps"
 license=('GPL')
 makedepends=('gcc-libs')
 depends=('i3-gaps')
 optdepends=('ttf-font-awesome')
 source=('https://github.com/Leinnan/i3gs/archive/master.zip'
 	'i3gs.conf')
 sha256sums=('2ce87310358883272c1d7185e5aa868384ef12dae16b3dfc5fc61830dde2e2fb'
            '539a241b830b7384dc89f824013eed93d7308d753e5c499ee747e6626c3eefeb')

 build() {
   cd "$srcdir/i3gs-master"
   make
 }

 package() {
   cd "$srcdir/i3gs-master"
   make DESTDIR=$pkgdir PREFIX=/usr
   make install
 }