
static void centeredmaster(Monitor *m);
static void centeredfloatingmaster(Monitor *m);

void
centeredmaster(Monitor *m)
{
	unsigned int i, n, h, mw, mx, my, oty, ety, tw;
	Client *c;
	
	/* count number of clients in the selected monitor */
	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	
	if (n == 0)
		return;
	if(n == 1){
		c = nexttiled(m->clients);
		resize(c, m->wx, m->wy, m->ww - 2 * c->bw, m->wh - 2 * c->bw, 0);
		return;
	}

	/* initialize areas */
	mw = m->ww;
	mx = 0;
	my = m->gappx;
	tw = mw;

	if (n > m->nmaster) {
		/* go mfact box in the center if more than nmaster clients */
		mw = m->nmaster ? m->ww * m->mfact : 0;
		tw = m->ww - mw;

		if (n - m->nmaster > 1) {
			/* only one client */
			mx = (m->ww - mw) / 2;
			tw = (m->ww - mw) / 2;
		}
	}

	oty = m->gappx;
	ety = m->gappx;
	for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
	if (i < m->nmaster) {
		/* nmaster clients are stacked vertically, in the center
		 * of the screen */
		h = (m->wh - my) / (MIN(n, m->nmaster) - i);
		if(m->nmaster >= n)
			resize(c, m->wx + mx + m->gappx, m->wy + my, mw - 2*(c->bw + m->gappx),
		       h - (2*c->bw) - m->gappx, 0);
		else if(m->nmaster + 1 < n)
			resize(c, m->wx + mx + m->gappx/2, m->wy + my, mw - 2*c->bw - m->gappx, h - 2*c->bw - m->gappx, 0);
		else
			resize(c, m->wx + mx + m->gappx, m->wy + my, mw - 2*c->bw - m->gappx*3/2, h - 2*c->bw - m->gappx, 0);
		if(my + HEIGHT(c) + m->gappx < m->mh)
			my += HEIGHT(c) + m->gappx;
	} else {
		/* stack clients are stacked vertically */
		if ((i - m->nmaster) % 2) {
			h = (m->wh - ety) / ( (1 + n - i) / 2);
			resize(c, m->wx + m->gappx, m->wy + ety, tw - (2*c->bw) - m->gappx*3/2, h - 2*c->bw - m->gappx, 0);
			if(ety + HEIGHT(c) + m->gappx < m->mh)
				ety += HEIGHT(c) + m->gappx;
		} else {
			h = (m->wh - oty) / ((1 + n - i) / 2);
			resize(c, m->wx + mx + mw + m->gappx/2, m->wy + oty, tw - (2*c->bw) - m->gappx*3/2, h - 2*c->bw - m->gappx, 0);
			if(oty + HEIGHT(c) + m->gappx < m->mh)
				oty += HEIGHT(c) + m->gappx;
		}
	}
}

void
centeredfloatingmaster(Monitor *m)
{
	unsigned int i, n, w, mh, mw, mx, mxo, my, myo, tx;
	Client *c;

	/* count number of clients in the selected monitor */
	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;
	if(n == 1){
		c = nexttiled(m->clients);
		resize(c, m->wx, m->wy, m->ww - 2 * c->bw, m->wh - 2 * c->bw, 0);
		return;
	}

	/* initialize nmaster area */
	if (n > m->nmaster) {
		/* go mfact box in the center if more than nmaster clients */
		if (m->ww > m->wh) {
			mw = m->nmaster ? m->ww * m->mfact : 0;
			mh = m->nmaster ? m->wh * 0.9 : 0;
		} else {
			mh = m->nmaster ? m->wh * m->mfact : 0;
			mw = m->nmaster ? m->ww * 0.9 : 0;
		}
		mx = mxo = (m->ww - mw + m->gappx) / 2;
		my = myo = (m->wh - mh) / 2;
	} else {
		/* go fullscreen if all clients are in the master area */
		mh = m->wh;
		mw = m->ww;
		mx = m->gappx;
		mxo = 0;
		my = myo = 0;
	}
	
	tx = m->gappx;
	for(i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
	if (i < m->nmaster) {
		/* nmaster clients are stacked horizontally, in the center
		 * of the screen */
		w = (mw + mxo - mx) / (MIN(n, m->nmaster) - i) + m->gappx;
		resize(c, m->wx + mx, m->wy + my + m->gappx, w - 2*(c->bw + m->gappx),
		       mh - 2*(c->bw + m->gappx), 0);
		if(mx + WIDTH(c) + m->gappx < m->mw)
			mx += WIDTH(c) + m->gappx;
	} else {
		/* stack clients are stacked horizontally */
		w = (m->ww - tx) / (n - i) + m->gappx;
		resize(c, m->wx + tx, m->wy + m->gappx, w - 2*(c->bw + m->gappx),
		       m->wh - 2*(c->bw + m->gappx), 0);
		if(tx + WIDTH(c) + m->gappx < m->mw)
			tx += WIDTH(c) + m->gappx;
	}
}
