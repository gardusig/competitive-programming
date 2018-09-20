class node {
public:
	node *left, *right;
	int lo, hi, lazy, value;
	node (const int _lo, const int _hi) {
		lazy = value = 0;
		lo = _lo, hi = _hi;
		left = right = NULL;
	}
	void build () {
		if (lo == hi)
			return;
		const int mid = (lo + hi) >> 1;
		left = new node(lo, mid);
		right = new node(mid + 1, hi);
		left->build(), right->build();
	}
	void propagate () {
		if (lazy) {
			value += lazy * (hi - lo + 1);
			if (lo != hi)
				left->lazy += lazy, right->lazy += lazy;
			lazy = 0;
		}
	}
	void update (const int _lo, const int _hi, const int new_value) {
		propagate();
		if (hi < _lo or lo > _hi)
			return;
		if (lo >= _lo and hi <= _hi) {
			lazy = new_value;
			propagate();
			return;
		}
		left->update(_lo, _hi, new_value);
		right->update(_lo, _hi, new_value);
		value = left->value + right->value;
	}
	int query (const int _lo, const int _hi) {
		propagate();
		if (hi < _lo or lo > _hi)
			return 0;
		if (lo >= _lo and hi <= _hi)
			return value;
		int a = left->query(_lo, _hi);
		int b = right->query(_lo, _hi);
		return a + b;
	}
};