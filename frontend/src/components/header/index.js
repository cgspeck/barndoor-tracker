import { h } from 'preact';
import { Link } from 'preact-router/match';
import style from './style.css';

const DebugLink = () => {
	if (process.env.NODE_ENV === 'development') {
		return <Link activeClassName={style.active} href="/debug">Debug</Link>
	}
}

const Header = () => (
	<header class={style.header}>
		<h1>Preact App</h1>
		<nav>
			<Link activeClassName={style.active} href="/">Home</Link>
			<DebugLink/>
		</nav>
	</header>
);

export default Header;
