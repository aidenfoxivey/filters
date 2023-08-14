# Filters! XORs, Blooms, Cuckoos, oh my!

I love filters. Primarily for coffee. Turkish coffee is good, but I don't like eating 
that many chunks of bean.

These are different filters. Magical data structures that exist to give us a rough idea of
when we need to actually check storage and when we can easily just brush off a query.

## Bloom Filters
Bloom filters operate based on the idea that they have limited false positives but will
never have a false negative. This means that we dramatically reduce the amount of costly
calls and speed up application.

## Cuckoo Filters
**to be finished**

## XOR Filters
**to be finished**

## Implementation

The implementation path is like this:
* ✅ basic bit-field data structure
* ✅ bloom filter
* bloom filter with run-length encoding
* cuckoo filter
* xor filter

Ideally we'll use a little bit of Python for some experiments to figure out whether the
accuracy of my implementation is actually close to the theoretical limit.
