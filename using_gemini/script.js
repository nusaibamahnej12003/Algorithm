class Node {
    constructor(char, freq, left = null, right = null) {
        this.char = char;
        this.freq = freq;
        this.left = left;
        this.right = right;
    }
}

function generateHuffman() {
    const text = document.getElementById('inputText').value;
    if (!text) return;

    // Step 1: Count frequencies
    const freqMap = {};
    for (let char of text) {
        freqMap[char] = (freqMap[char] || 0) + 1;
    }

    // Step 2: Create leaf nodes and push to a "priority queue" (sorted array)
    let pq = [];
    for (let char in freqMap) {
        pq.push(new Node(char, freqMap[char]));
    }

    // Step 3: Build the tree
    while (pq.length > 1) {
        pq.sort((a, b) => a.freq - b.freq); // Simple min-priority queue behavior
        let left = pq.shift();
        let right = pq.shift();

        let newNode = new Node('$', left.freq + right.freq, left, right);
        pq.push(newNode);
    }

    const root = pq[0];
    const codes = {};
    
    // Step 4: Traverse tree to generate codes
    function buildCodes(node, currentCode) {
        if (!node) return;
        if (!node.left && !node.right) {
            codes[node.char] = currentCode;
            return;
        }
        buildCodes(node.left, currentCode + "0");
        buildCodes(node.right, currentCode + "1");
    }

    buildCodes(root, "");

    // Step 5: Update UI
    displayResults(freqMap, codes, text);
}

function displayResults(freqMap, codes, originalText) {
    const tableBody = document.getElementById('tableBody');
    const outputDiv = document.getElementById('output');
    const encodedOutput = document.getElementById('encodedOutput');
    
    tableBody.innerHTML = "";
    for (let char in codes) {
        const row = `<tr>
            <td>${char === " " ? "[Space]" : char}</td>
            <td>${freqMap[char]}</td>
            <td><code>${codes[char]}</code></td>
        </tr>`;
        tableBody.innerHTML += row;
    }

    let encodedText = "";
    for (let char of originalText) {
        encodedText += codes[char];
    }

    encodedOutput.innerText = encodedText;
    outputDiv.style.display = "block";
}