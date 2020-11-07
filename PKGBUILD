# Maintainer: Amadej Kastelic <amadejkastelic7@gmail.com>
pkgname=SimpleVideoEditor
pkgver=0.1.0
pkgrel=1
epoch=
pkgdesc="Simple video and photo editor."
arch=("x86_64")
url=""
license=("GPL")
groups=()
depends=("qt5-base" "qt5-multimedia" "qt5-quickcontrols2" "libopenshot-audio" "libopenshot")
makedepends=()
checkdepends=()
optdepends=()
provides=()
conflicts=()
replaces=()
backup=()
options=()
install=
changelog=
source=("$pkgname-$pkgver-Linux.tar.gz")
noextract=()
md5sums=(409e06e43c3e7f2de7fff4e2ac6730bd)
validpgpkeys=()

package() {
	echo -e "Current dir: "
	pwd
	echo
	tar -xvf $source
        chmod +x ./usr/local/bin/svpeditor
	sudo cp ./usr/local/bin/svpeditor /usr/bin/sveditor
}
