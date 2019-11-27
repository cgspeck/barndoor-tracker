import MiniCssExtractPlugin from 'mini-css-extract-plugin';

export default (config, env, helpers) => {
	if (env.isProd) {
		config.devtool = false;
		config.output.filename = `[contenthash].js`;
		config.output.chunkFilename = `[contenthash].js`;
	}

	// config.plugins.push( new CopyWebpackPlugin([{ context: `${__dirname}/src/assets`, from: `*.*` }]) );
	config.plugins.push( new MiniCssExtractPlugin({
		filename: `[contenthash].css`,
		chunkFilename: `[contenthash].css`
	}));
	// config.module.loaders.push({ test: /\.css$/, loader: ['mini-css-extract-plugin']});

	/*module: {
    rules: [
      {
        test: /\.css$/,
        use: [
          {
            loader: MiniCssExtractPlugin.loader,
            options: {
              publicPath: (resourcePath, context) => {
                // publicPath is the relative path of the resource to the context
                // e.g. for ./css/admin/main.css the publicPath will be ../../
                // while for ./css/main.css the publicPath will be ../
                return path.relative(path.dirname(resourcePath), context) + '/';
              },
            },
          },
          'css-loader',
        ],
      },
    ],
	},*/
	// let { rules } = helpers.getRules;
	// rules.push( new RuleWrapper)
};

