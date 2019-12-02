import { h } from 'preact';
import style from './style';

import TextField from 'preact-material-components/TextField';
import 'preact-material-components/TextField/style.css';

const Align = () => (
	<div class={style.align}>
		<h1>Align</h1>
		<h2>STATUS</h2>
		<div>
			<p>
				<TextField label="Azimuth" value='160 >>'></TextField>
				<br/>
				AZ target: 180
			</p>
			<p>
				<TextField label="Altitude" value='20 /\/\'></TextField>
				<br/>
				ALT target: 37.4
			</p>
		</div>
	</div>
);

export default Align;
