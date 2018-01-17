to_unsigned.h: C and C++ code convert an integer of any size to unsigned

to_unsigned.h is C and C++ .h file defining the macro or function
TO_UNSIGNED(x), which converts an integer x to the equivalent unsigned type
of the same size. Thus TO_UNSIGNED((char)-3) == 253, and
TO_UNSIGNED(((short)-3) == 65533 (typically).

__END__
