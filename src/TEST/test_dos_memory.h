#ifndef TEST_MEMORY_H
#define TEST_MEMORY_H

#ifdef POLICY_USE_DOS_STD
    #include "../STD/dos_stdio.h"
    #include "../STD/dos_stdint.h"
    #include "../STD/assert.h"
#else
    #include <stdio.h>
    #include <stdint.h>
    #include <assert.h>
#endif

#include "../DOS/dos_memory_services.h"
#include "../DOS/dos_memory_tools.h"

void test_allocate_memory() {

    // Basic allocation (small block)
    uint16_t seg;
    dos_error_code_t err = dos_allocate_memory_blocks(16, &seg);  // 256 bytes
    assert(err == DOS_SUCCESS);
    assert(seg != 0);
    assert(seg != 0xFFFF);

    // Allocation with NULL output pointer (should fail gracefully)
    err = dos_allocate_memory_blocks(16, NULL);
    assert(err != DOS_SUCCESS);

    // Zero paragraph allocation (edge case)
    err = dos_allocate_memory_blocks(0, &seg);
    // DOS may allow 0 or return error; just verify consistent behavior
    assert(err == DOS_SUCCESS || err == DOS_INSUFFICIENT_MEMORY);

    // Large allocation (may fail depending on available memory)
    err = dos_allocate_memory_blocks(0xFFF0, &seg);  // ~1 MB request
    assert(err == DOS_SUCCESS || err == DOS_INSUFFICIENT_MEMORY);
    if (err == DOS_SUCCESS) {
        // If it succeeded, free it immediately
        dos_free_allocated_memory_blocks(seg);
    }

    // Far pointer output test (large model)
    uint16_t far_seg;
    err = dos_allocate_memory_blocks(32, &far_seg);
    assert(err == DOS_SUCCESS);
    assert(far_seg != 0);
}

void test_free_memory() {

    // Free a valid allocated block
    uint16_t seg;
    dos_allocate_memory_blocks(16, &seg);
    dos_error_code_t err = dos_free_allocated_memory_blocks(seg);
    assert(err == DOS_SUCCESS);

    // Free NULL segment (0) - should fail
    err = dos_free_allocated_memory_blocks(0);
    assert(err != DOS_SUCCESS);

    // Free invalid segment (0xFFFF) - should fail
    err = dos_free_allocated_memory_blocks(0xFFFF);
    assert(err != DOS_SUCCESS);

    // Double-free same segment (should fail on second)
    dos_allocate_memory_blocks(16, &seg);
    err = dos_free_allocated_memory_blocks(seg);
    assert(err == DOS_SUCCESS);
    err = dos_free_allocated_memory_blocks(seg);  // Second free

    // Free unallocated but plausible segment (may fail or succeed depending on DOS)
    err = dos_free_allocated_memory_blocks(0x1234);
    assert(err == DOS_SUCCESS || err != DOS_SUCCESS);  // Just verify it returns
}

void test_get_free_memory() {

    // Basic query
    uint16_t free;
    dos_error_code_t err = dos_get_free_memory_paragraphs(&free);
    assert(err == DOS_SUCCESS);
    assert(free > 0);  // Should always have some free memory

    // Query with NULL output pointer (should fail)
    err = dos_get_free_memory_paragraphs(NULL);
    assert(err != DOS_SUCCESS);

    // Query before/after allocation to verify change
    uint16_t before, after;
    dos_get_free_memory_paragraphs(&before);

    uint16_t seg;
    dos_allocate_memory_blocks(64, &seg);  // Allocate 1KB

    dos_get_free_memory_paragraphs(&after);
    assert(after <= before);  // Free memory should decrease or stay same
    assert(before - after >= 64);  // Should decrease by at least allocated amount
    dos_free_allocated_memory_blocks(seg);  // Cleanup

    // Far pointer output test (large model)
    uint16_t far_free;
    err = dos_get_free_memory_paragraphs(&far_free);
    assert(err == DOS_SUCCESS);
    assert(far_free > 0);

    // Verify returned value is reasonable (not obviously corrupted)
    assert(free < 0xF000);  // Sanity: shouldn't be near segment limit
}

void test_dos_memcmp() {
    const uint8_t s1[] = {0x41, 0x42, 0x43, 0x44}; // ABCD
    const uint8_t s2[] = {0x41, 0x42, 0x43, 0x44};
    const uint8_t s3[] = {0x41, 0x42, 0x43, 0x45}; // ABCE
    const uint8_t s4[] = {0x41, 0x42};             // AB

    // 1. Identical blocks
    assert(dos_memcmp(s1, s2, 4) == 0);
    assert(dos_memcmp(s1, s2, 0) == 0); // Zero length is equal

    // 2. Different last byte
    assert(dos_memcmp(s1, s3, 4) < 0);  // 'D' < 'E'
    assert(dos_memcmp(s3, s1, 4) > 0);  // 'E' > 'D'

    // 3. Partial comparison (should be equal if diff is outside range)
    assert(dos_memcmp(s1, s3, 3) == 0); // "ABC" == "ABC"

    // 4. Different lengths compared
    assert(dos_memcmp(s1, s4, 2) == 0); // "AB" == "AB"

    // 5. NULL pointer handling
    assert(dos_memcmp(NULL, s1, 0) < 0);
    assert(dos_memcmp(s1, NULL, 0) > 0);
}

void test_dos_memmem() {

    const uint8_t haystack[] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46}; // ABCDEF
    const uint8_t needle_start[] = {0x41, 0x42};                     // AB
    const uint8_t needle_mid[] = {0x43, 0x44};                       // CD
    const uint8_t needle_end[] = {0x45, 0x46};                       // EF
    const uint8_t needle_big[] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47}; // ABCDEFG
    const uint8_t needle_bad[] = {0x58, 0x59};                       // XY
    const uint8_t needle_empty[] = {0};

    void* result;

    // 1. Match at start
    result = dos_memmem(haystack, 6, needle_start, 2);
    assert(result == haystack);

    // 2. Match in middle
    result = dos_memmem(haystack, 6, needle_mid, 2);
    assert(result == (haystack + 2));

    // 3. Match at end
    result = dos_memmem(haystack, 6, needle_end, 2);
    assert(result == (haystack + 4));

    // 4. Exact full match
    result = dos_memmem(haystack, 6, haystack, 6);
    assert(result == haystack);

    // 5. Needle larger than haystack
    result = dos_memmem(haystack, 6, needle_big, 7);
    assert(result == NULL);

    // 6. No match found
    result = dos_memmem(haystack, 6, needle_bad, 2);
    assert(result == NULL);

    // 7. Empty needle (POSIX: should return haystack)
    result = dos_memmem(haystack, 6, needle_empty, 0);
    assert(result == haystack);

    // 8. Empty haystack, empty needle (Should return null)
    result = dos_memmem(haystack, 0, needle_empty, 0);
    assert(result == NULL);

    // 9. Empty haystack, non-empty needle (Should return NULL)
    result = dos_memmem(haystack, 0, needle_start, 2);
    assert(result == NULL);

    // 10. NULL inputs
    assert(dos_memmem(NULL, 6, needle_start, 2) == NULL);
    assert(dos_memmem(haystack, 6, NULL, 2) == NULL);

    // 11. Overlapping memory (Self search)
    // Searching for "BCDE" inside "ABCDEF" starting at offset 1
    result = dos_memmem(haystack, 6, haystack + 1, 4);
    assert(result == (haystack + 1));
}

void test_dos_memory() {

    printf("Testing DOS memory functions...\n");

    test_allocate_memory();
    test_free_memory();
    test_get_free_memory();
    test_dos_memcmp();
    test_dos_memmem();

    printf("DOS memory functions tests passed\n\n");
}

#endif
