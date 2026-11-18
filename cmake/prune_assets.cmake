# Removes from the build's assets/ every file that assets/ no longer has (a description dropped from assets/ad kept
# playing from the build's stale copy). Run with -DSRC=<source assets> -DDST=<build assets>.
file(GLOB_RECURSE built RELATIVE "${DST}" "${DST}/*")
foreach(f IN LISTS built)
  if(NOT EXISTS "${SRC}/${f}")
    file(REMOVE "${DST}/${f}")
    message(STATUS "assets: removed stale ${f}")
  endif()
endforeach()
