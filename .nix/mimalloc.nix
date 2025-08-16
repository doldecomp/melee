{ lib
, stdenv
, fetchFromGitHub
}:

stdenv.mkDerivation rec {
  pname = "mimalloc";
  version = "3.1.5";

  src = fetchFromGitHub {
    owner = "microsoft";
    repo = "mimalloc";
    rev = "v${version}";
    hash = "sha256-D25BooCa48IGY7FZQoVW2u8U6BVIcGt7eiwmvT8wsKE=";
  };

  meta = with lib; {
    description = "mimalloc is a compact general purpose allocator with excellent performance.";
    homepage = "https://github.com/microsoft/mimalloc";
    license = licenses.mit;
    maintainers = with maintainers; [ r-burns ];
    platforms = [ "i686-linux" ];
  };
}
