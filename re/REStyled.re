open BsReactNative;

let get = (arg, default) =>
  switch arg {
  | None => default
  | Some(value) => value
  };

module type StyledConfig = {type styleParams; let style: option(styleParams) => Style.t;};

module View = (Config: StyledConfig) => {
  let make = (~styled=?, ~style as additionalStyle=Style.(style([]))) =>
    View.make(~style=Style.combine(Config.style(styled), additionalStyle));
};

module Text =
       (
         Config: {
           type styleParams;
           let defaultParams: styleParams;
           let style: (~params: styleParams) => Style.t;
         }
       ) => {
  let make = (~styled=?, ~style as additionalStyle=Style.(style([]))) => {
    let params = get(styled, Config.defaultParams);
    Text.make(~style=Style.combine(Config.style(~params), additionalStyle))
  };
};

module ScrollView = (Config: StyledConfig) => {
  let make = (~styled=?, ~style as additionalStyle=Style.(style([]))) =>
    ScrollView.make(~style=Style.combine(Config.style(styled), additionalStyle));
};

module TouchableOpacity = (Config: StyledConfig) => {
  let make = (~styled=?, ~style as additionalStyle=Style.(style([]))) =>
    TouchableOpacity.make(~style=Style.combine(Config.style(styled), additionalStyle));
};

module TextInput = (Config: StyledConfig) => {
  let make = (~styled=?, ~style as additionalStyle=Style.(style([]))) =>
    TextInput.make(
      ~style=
        Style.combine(
          switch styled {
          | Some(params) => Config.style(params)
          | None => Style.style([])
          },
          additionalStyle
        )
    );
};

module Image = (Config: StyledConfig) => {
  let make = (~styled=?, ~style as additionalStyle=Style.(style([]))) =>
    Image.make(~style=Style.combine(Config.style(styled), additionalStyle));
};