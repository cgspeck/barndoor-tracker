import { h } from 'preact';
import style from './style';

import Button from 'preact-material-components/Button';
import 'preact-material-components/Button/style.css';
import Switch from 'preact-material-components/Switch';
import 'preact-material-components/Switch/style.css';
import TextField from 'preact-material-components/TextField';
import 'preact-material-components/TextField/style.css';

const Home = () => (
	<div class={style.home}>
		<h1>Track</h1>
		<h2>STATUS</h2>
		<div>
			<h2>Locate</h2>
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
		<div>
			<h2>Control</h2>
			<p>
				<Button raised ripple onClick={e => e.prevent_default}>Home</Button>
			</p>
			<p>
				<Button raised ripple onClick={e => e.prevent_default}>Start</Button>
			</p>
			<p>
				<TextField label="Tracking time (minutes)" value='300'></TextField>
			</p>
			<p>
				<Button raised ripple onClick={e => e.prevent_default}>Stop</Button>
			</p>
		</div>
		<div>
			<h2>Intervalometer</h2>
			<p>
				Enabled:   <Switch></Switch>
			</p>
			<p>
				<TextField label="Bulb (seconds)" value='15'></TextField>
			</p>
			<p>
				<TextField label="Rest (seconds)" value='15'></TextField>
			</p>
		</div>
		<div>
			<h2>Dew Heater</h2>
			Enabled:   <Switch></Switch>
		</div>

	</div>
);

export default Home;
