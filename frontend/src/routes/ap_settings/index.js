import { h, Component } from 'preact';
import style from './style';
import { getAPSettings, setAPSettings } from '../../lib/settings';

export default class APSettings extends Component {
	state = {
		apSettings: {
			ssid: null,
			key: null
		},
		error: null,
		info: null,
	};

	async componentDidMount() {
		getAPSettings()
			.then(r => this.setState({ apSettings: {...r} }))
			.catch(e => this.handleError(e));
	}

	handleError = e => {
		console.error('problem', e)
		this.setState({error: e});
	}

	onSubmit = e => {
		e.preventDefault();
		this.setState({error: null, info: null});
		const { ssid, key } = this.state.apSettings;
		setAPSettings(ssid, key)
			.then(r => this.setState({ info: "AP settings updated, device will restart soon" }))
			.catch(e => this.handleError(e));
  }

  onSSIDInput = e => {
    const { value } = e.target;
		this.setState({ apSettings: {
			key: this.state.apSettings.key,
			ssid: value
		} });
	}

	onKeyInput = e => {
    const { value } = e.target;
		this.setState({
			apSettings: {
				key: value,
				ssid: this.state.apSettings.ssid
		} });
  }

	errorToast() {
		if (this.state.error != null) {
			return(
				<p>
					{ this.state.error.toString() }
				</p>
			)
		}
	}

	infoToast() {
		if (this.state.info != null) {
			return(
				<p>
					{ this.state.info.toString() }
				</p>
			)
		}
	}

	render({}, { apSettings }) {
		return(
			<div class={style.ap}>
				<h1>Access Point Settings</h1>
				{this.infoToast()}
				{this.errorToast()}
				<form onSubmit={this.onSubmit.bind(this)}>
					<p>SSID: <input type="text" value={apSettings.ssid} onInput={this.onSSIDInput.bind(this)}/></p>
					<p>Key: <input type="text" value={apSettings.key} onInput={this.onKeyInput.bind(this)}/></p>
					<button type="submit">Update</button>
				</form>
			</div>
		)
	}
};
