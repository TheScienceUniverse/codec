function huffmanEncode(msg) {
	// find distinct characters, frequency, code
	var i, j;
	var S = [], t;
	for (i = 0; i < msg.length; i++) {
		t = false;
		for (j = 0; j < S.length; j++) {
			if (S[j][0] == msg[i]) {
				++S[j][1];
				t = true;
				break;
			}
		}
		if (t == false) {
			S.push([msg[i], 1, ""]);
		}
	}
	var T = [];
	for (i = 0; i < S.length; i++) {
		T.push([S[i][1], null, null, null, ""]);
	}
	while (countOrphanNodes(T) > 1) {
		let X = [];
		for (i = 0; i < T.length; i++) {
			if (T[i][1] == null) {
				X.push([T[i][0], i]);
			}
		}
		t = findMin2Indeces(X);
		T[t[0]][1] = T.length;
		T[t[1]][1] = T.length;
		T.push([T[t[0]][0] + T[t[1]][0], null, t[0], t[1], ""]);
	}
	for (i = T.length - 1; i > S.length - 1; i--) {
		T[T[i][2]][4] = T[i][4] + "0";
		T[T[i][3]][4] = T[i][4] + "1";
	}
	for (i = 0; i < S.length; i++) {
		S[i][2] = T[i][4];
	}
	// encoding the message
	var eMsg = "M";
	for (i = 0; i < S.length; i++) {
		eMsg += S[i][2] + S[i][0];
	}
	eMsg += "D";
	for (i = 0; i < msg.length; i++) {
		for (j = 0; j < S.length; j++) {
			if (msg[i] == S[j][0]) {
				eMsg += S[j][2];
				break;
			}
		}
	}
	return eMsg;
}

function huffmanDecode(msg) {
	var dMsg = "";
	class node {
		constructor(d, lc, rc) {
			this.data = d;
			// this.parent = p; => NOT REQUIRED
			this.childL = lc;
			this.childR = rc;
		}
	}
	// creating symbol table
	var root = new node(null, null, null);
	var i = 0;
	if (msg[0] == "M") {
		let p = root;
		while (msg[++i] != "D") {
			if (msg[i] == "0") {
				if (p.childL == null) {
					p.childL = new node(null, null, null);
				}
				p = p.childL;
			} else if (msg[i] == "1") {
				if (p.childR == null) {
					p.childR = new node(null, null, null);
				}
				p = p.childR;
			} else {
				p.data = msg[i];
				p = root;
			}
		}
	} else {
		dMsg = "SORRY...CORRUPTED DATA";
	}
	// console.log(root);
	// decoding message
	for (++i; i < msg.length; i++) {
		p = root;
		do {
			console.log(i, msg[i]);
			if (msg[i] == "0") {
				p = p.childL;
			} else if (msg[i] == "1") {
				p = p.childR;
			}
			++i;
			if (i == msg.length) {
				break;
			}
		} while (p.childL != null || p.childR != null);
		dMsg += p.data;
		--i;
		p = root;
	}
	return dMsg;
}

function findMin2Indeces (A) {
	var m1i = 0, m2i = 1;
	for (var i = 1; i < A.length; i++) {
		if (A[i][0] < A[m1i][0]) {
			m2i = m1i;
			m1i = i;
		} else if (A[i][0] < A[m2i][0]) {
			m2i = i;
		}
	}
	return [A[m1i][1], A[m2i][1]];
}

function countOrphanNodes (T) {
	var c = 0;
	for (var i = 0; i < T.length; i++) {
		if (T[i][1] == null) {
			++c;
		}
	}
	return c;
}