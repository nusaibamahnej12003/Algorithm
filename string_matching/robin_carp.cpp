// Function to search for all occurrences of 'pat' in 'txt'
// using Rabin-Karp
function search(pat, txt)
{

    // Number of characters in the input alphabet (ASCII)
    let d = 256;

    // A prime number for modulo operations to reduce
    // collisions
    let q = 101;

    // Length of the pattern
    let m = pat.length;

    // Length of the text
    let n = txt.length;

    // Hash value for pattern
    let p = 0;

    // Hash value for current window of text
    let t = 0;

    // High-order digit multiplier
    let h = 1;

    let ans = [];

    // Precompute h = pow(d, m-1) % q
    for (let i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Compute initial hash values for pattern and first
    // window of text
    for (let i = 0; i < m; i++) {
        p = (d * p + pat.charCodeAt(i)) % q;
        t = (d * t + txt.charCodeAt(i)) % q;
    }

    // Slide the pattern over text one by one
    for (let i = 0; i <= n - m; i++) {

        // If hash values match, check characters one by one
        if (p === t) {
            let match = true;
            for (let j = 0; j < m; j++) {
                if (txt[i + j] !== pat[j]) {
                    match = false;
                    break;
                }
            }
            if (match)
                ans.push(i);
        }

        // Calculate hash value for the next window
        if (i < n - m) {
            t = (d * (t - txt.charCodeAt(i) * h)
                 + txt.charCodeAt(i + m))
                % q;
            if (t < 0)
                t += q;
        }
    }
    return ans;
}

// driver code
let txt = "geeksforgeeks";
let pat = "geeks";
let res = search(pat, txt);
console.log(res.join(" "));