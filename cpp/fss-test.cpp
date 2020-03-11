#include <chrono>
#include "fss-common.h"
#include "fss-server.h"
#include "fss-client.h"

int main()
{
    // Set up variables
    uint64_t a = 1024;
    uint64_t b = 10;
    Fss fClient, fServer;
    ServerKeyLt_lonhh k0;
    ServerKeyLt_lonhh k1;

    // Initialize client, use 10 bits in domain as example
    initializeClient(&fClient, 64, 2); 
    
    // Equality FSS test
    
    initializeServer(&fServer, &fClient);
    
    uint64_t lt_ans0, lt_ans1, lt_fin;

    //lt_ans0 = evaluateLt_lonhh(&fServer, &k0, a-1);
    //lt_ans1 = evaluateLt_lonhh(&fServer, &k1, a-1);
    //cout << lt_ans0 - lt_ans1 << endl;
    int nr_error = 0;
    for(a=0;a<1024;a++) {
        generateTreeLt_lonhh(&fClient, &k0, &k1, a, b);
        for(int i=0;i<2048;i++) {
            lt_ans0 = evaluateLt_lonhh(&fServer, &k0, i);
            lt_ans1 = evaluateLt_lonhh(&fServer, &k1, i);
            if((i < a) && (lt_ans0 - lt_ans1 != b)) {
                nr_error++;
            } else if((i >= a) && (lt_ans0 - lt_ans1 != 0)) {
                nr_error++;
            }
        }
        if(nr_error)
            cout << a << endl;
    }
    //lt_fin = lt_ans0 - lt_ans1;
    //cout << "FSS Lt Match (should be non-zero): " << lt_fin << endl;

}
/*    
    // Initialize server
    initializeServer(&fServer, &fClient);
    mpz_class ans0, ans1, fin;
    
    ans0 = evaluateLt(&fServer, &k0, a);
    ans1 = evaluateEq(&fServer, &k1, a);
    fin = ans0 - ans1;
    cout << "FSS Eq Match (should be non-zero): " << fin << endl;
    
    ans0 = evaluateEq(&fServer, &k0, (a-1));
    ans1 = evaluateEq(&fServer, &k1, (a-1));
    fin = ans0 - ans1;
    cout << "FSS Eq No Match (should be 0): " << fin << endl;

    // Less than FSS test
    ServerKeyLt lt_k0;
    ServerKeyLt lt_k1;
    
    initializeClient(&fClient, 10, 2);
    generateTreeLt(&fClient, &lt_k0, &lt_k1, a, b);

    initializeServer(&fServer, &fClient);
    uint64_t lt_ans0, lt_ans1, lt_fin;

    lt_ans0 = evaluateLt(&fServer, &lt_k0, (a-1));
    lt_ans1 = evaluateLt(&fServer, &lt_k1, (a-1));
    lt_fin = lt_ans0 - lt_ans1;
    cout << "FSS Lt Match (should be non-zero): " << lt_fin << endl;

    lt_ans0 = evaluateLt(&fServer, &lt_k0, a);
    lt_ans1 = evaluateLt(&fServer, &lt_k1, a);
    lt_fin = lt_ans0 - lt_ans1;
    cout << "FSS Lt No Match (should be 0): " << lt_fin << endl;

    // Equality FSS test for multi-parties
    MPKey mp_keys[3];
    initializeClient(&fClient, 10, 3);
    generateTreeEqMParty(&fClient, a, b, mp_keys);

    initializeServer(&fServer, &fClient);
    uint32_t mp_ans0 = evaluateEqMParty(&fServer, &mp_keys[0], a);
    uint32_t mp_ans1 = evaluateEqMParty(&fServer, &mp_keys[1], a);
    uint32_t mp_ans2 = evaluateEqMParty(&fServer, &mp_keys[2], a);
    uint32_t xor_mp = mp_ans0 ^ mp_ans1 ^ mp_ans2;
    cout << "FSS Eq Multi-Party Match (should be non-zero): " << xor_mp << endl;

    mp_ans0 = evaluateEqMParty(&fServer, &mp_keys[0], (a+1));
    mp_ans1 = evaluateEqMParty(&fServer, &mp_keys[1], (a+1));
    mp_ans2 = evaluateEqMParty(&fServer, &mp_keys[2], (a+1));
    xor_mp = mp_ans0 ^ mp_ans1 ^ mp_ans2;
    cout << "FSS Eq Multi-Party No Match (should be 0): " << xor_mp << endl;

    size_t rounds = 100000;
    auto t_begin = std::chrono::high_resolution_clock::now();
    for(size_t i=0; i<rounds; i++) {
        volatile auto x = evaluateEq(&fServer, &k0, i);
    }
    for(size_t i=0; i<rounds; i++) {
        volatile auto x = evaluateLt(&fServer, &lt_k0, i);
    }
    for(size_t i=0; i<rounds; i++) {
        volatile auto x = evaluateEqMParty(&fServer, &mp_keys[1], a);
    }
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Benchmark result: " <<
     std::chrono::duration<double, std::milli>(t_end - t_begin).count()
     << " ms" << endl;
    return 1;
}
*/