%ifndef __csym_include__
%define __csym_include__

%macro csym 1

%ifdef CYGWIN
%define %1 _%1
%endif

%ifdef LINUX
%define x x
%endif

%endmacro

%endif

