static void bstack(Monitor *);
static void bstackhoriz(Monitor *);

void
bstack(Monitor *m)
{
	unsigned int i, n, w, mh, mx, tx, ns;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;
	if(n == 1){
		c = nexttiled(m->clients);
		resize(c, m->wx, m->wy, m->ww - 2 * c->bw, m->wh - 2 * c->bw, 0);
		return;
	}

	if (n > m->nmaster){
		mh = m->nmaster ? m->wh * m->mfact : m->gappx;
		ns = 2;
	}
	else{
		mh = m->wh;
		ns = 1;
	}
	for (i = 0, mx = tx = m->gappx, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
		if (i < m->nmaster) {
			w = (m->ww - mx) / (MIN(n, m->nmaster) - i) - m->gappx;
			resize(c, m->wx + mx, m->wy + m->gappx, w - 2*c->bw, mh - 2*c->bw - m->gappx*(5-ns)/2, 0);
			if(mx + WIDTH(c) + m->gappx < m->mw)
				mx += WIDTH(c) + m->gappx;
		} else {
			w = (m->ww - tx) / (n - i) - m->gappx;
			if(m->nmaster == 0)
				resize(c, m->wx + tx, m->wy + mh, w - (2*c->bw), m->wh - mh - 2*c->bw - m->gappx, False);
			else
				resize(c, m->wx + tx, m->wy + mh + m->gappx/ns, w - (2*c->bw), m->wh - mh - 2*c->bw - m->gappx*(5-ns)/2, False);
			if (tx + WIDTH(c) + m->gappx < m->mw)
				tx += WIDTH(c) + m->gappx;
		}
}

void
bstackhoriz(Monitor *m)
{
	unsigned int i, n;
	int mx = 0, my = 0, mh = 0, mw = 0;
	int sx = 0, sy = 0, sh = 0, sw = 0;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

	if (n == 1) {
		c = nexttiled(m->clients);
		resize(c, m->wx, m->wy, m->ww - 2 * c->bw, m->wh - 2 * c->bw, 0);
		return;
	}

	sx = mx = m->wx + m->gappx;
	sy = my = m->wy + m->gappx;
	sh = mh = m->wh - 2*m->gappx;
	sw = mw = m->ww - 2*m->gappx - m->gappx * (MIN(n, m->nmaster) - 1);

	if (m->nmaster && n > m->nmaster) {
		sh = (mh - m->gappx) * (1 - m->mfact);
		mh = (mh - m->gappx) * m->mfact;
		sy = my + mh + m->gappx;
		sh = m->wh - mh - 2*m->gappx - m->gappx * (n - m->nmaster);
		sw = m->ww - 2*m->gappx;
	}

	for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
		if (i < m->nmaster) {
			resize(c, mx, my, mw / MIN(n, m->nmaster) - (2*c->bw), mh - (2*c->bw), 0);
			if(mx + WIDTH(c) + m->gappx < m->mw)
				mx += WIDTH(c) + m->gappx;
		} else {
			resize(c, sx, sy, sw - (2*c->bw), sh / (n - MIN(n, m->nmaster)) - (2*c->bw), 0);
			if(sy + HEIGHT(c) + m->gappx < m->mh)
				sy += HEIGHT(c) + m->gappx;
		}
	}
}
