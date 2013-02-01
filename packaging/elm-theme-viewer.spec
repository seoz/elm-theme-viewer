Name:       elm-theme-viewer
Summary:    elementary theme previewer
Version:    0.1
Release:    1
Group:      Utility
License:    BSD
URL:        https://github.com/seoz/elm-theme-viewer
Source0:    %{name}-%{version}.tar.gz
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  pkgconfig(eina)
BuildRequires:  pkgconfig(ecore)
BuildRequires:  pkgconfig(evas)
BuildRequires:  pkgconfig(edje)
BuildRequires:  pkgconfig(elementary)
BuildRequires:   edje-tools

%description
Elm Theme Viewer - EFL(Enlightenment Foundation Libraries) elementary widget preview program.

%prep
%setup -q

%build
export CFLAGS+=" -fPIC -Wall -g"
export LDFLAGS+=" -Wl,--hash-style=both -Wl,--as-needed"

%autogen
%configure

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

%files
%defattr(-,root,root,-)
%manifest %{name}.manifest
/usr/bin/elm_theme_viewer
/usr/share/elm-theme-viewer/images
/usr/share/elm-theme-viewer/themes
