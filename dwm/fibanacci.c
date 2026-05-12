
void
fibonacci(Monitor *mon, int s)
{
	unsigned int n, i, nx, ny, nw, nh;
	Client *c;

	for (n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

	nx = mon->wx;
	ny = mon->wy;
	nw = mon->ww;
	nh = mon->wh;

	for (i = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), i++) {
		if ((i % 2 && nh > 2 * mon->gappov) || (!(i % 2) && nw > 2 * mon->gappoh)) {
			if (i < n - 1) {
				if (i % 2)
					nh /= 2;
				else
					nw /= 2;
				if (i % 4 == 2)
					nx += nw;
				else if (i % 4 == 3)
					ny += nh;
			}
			if ((i % 4) == 0) {
				if (s)
					ny += nh;
				else
					ny -= nh;
			}
			else if ((i % 4) == 1)
				nx += nw;
			else if ((i % 4) == 2)
				ny += nh;
			else if ((i % 4) == 3) {
				if (s)
					nx += nw;
				else
					nx -= nw;
			}
			if (i == 0)	{
				if (n != 1)
					nw = mon->ww * mon->mfact;
				ny = mon->wy;
			}
			else if (i == 1)
				nw = mon->ww - nw;
		}
		resize(c, nx, ny, nw - 2 * c->bw, nh - 2 * c->bw, False);
	}
}

void
dwindle(Monitor *mon)
{
	fibonacci(mon, 1);
}

void
spiral(Monitor *mon)
{
	fibonacci(mon, 0);
}
