"""Gives the player the placeholder rifle (decision 0002, second pass). Safe to run more than once.

Run headless:
  UnrealEditor-Cmd UntilDawn.uproject -run=pythonscript -script=<this file> -unattended -nullrhi
"""
import unreal

ACTIONS = "/Game/Input/Actions"
IMC_DEFAULT = "/Game/Input/IMC_Default"
IA_SHOOT = "/Game/Variant_Shooter/Input/Actions/IA_Shoot"
CHARACTER_BP = "/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"
RIFLE_BP = "/Game/Variant_Shooter/Blueprints/Pickups/Weapons/BP_ShooterWeapon_Rifle"

assets = unreal.EditorAssetLibrary


def make_action(name):
    """Bool hold action, same as IA_Aim."""
    path = f"{ACTIONS}/{name}"
    if not assets.does_asset_exist(path):
        assets.duplicate_asset(f"{ACTIONS}/IA_Aim", path)
    return unreal.load_asset(path)


def map_keys(imc, action, key_names):
    mapped = {
        (m.get_editor_property("action").get_name(), str(m.get_editor_property("key").get_editor_property("key_name")))
        for m in imc.get_editor_property("default_key_mappings").get_editor_property("mappings")
    }
    for key_name in key_names:
        if (action.get_name(), key_name) not in mapped:
            key = unreal.Key()
            key.set_editor_property("key_name", key_name)
            imc.map_key(action, key)


shoot = unreal.load_asset(IA_SHOOT)
sprint = make_action("IA_Sprint")
reload = make_action("IA_Reload")

imc = unreal.load_asset(IMC_DEFAULT)
map_keys(imc, shoot, ["LeftMouseButton", "Gamepad_RightTriggerAxis"])
map_keys(imc, sprint, ["LeftShift", "Gamepad_LeftThumbstick"])
map_keys(imc, reload, ["R", "Gamepad_FaceButton_Left"])

bp = unreal.load_asset(CHARACTER_BP)
if not isinstance(unreal.get_default_object(bp.generated_class()), unreal.ShooterCharacter):
    unreal.BlueprintEditorLibrary.reparent_blueprint(bp, unreal.ShooterCharacter.static_class())
unreal.BlueprintEditorLibrary.compile_blueprint(bp)

cdo = unreal.get_default_object(bp.generated_class())
cdo.set_editor_property("FireAction", shoot)
cdo.set_editor_property("SprintAction", sprint)
cdo.set_editor_property("ReloadAction", reload)
cdo.set_editor_property("StartingWeaponClass", unreal.load_asset(RIFLE_BP).generated_class())

for path in [f"{ACTIONS}/IA_Sprint", f"{ACTIONS}/IA_Reload", IMC_DEFAULT, CHARACTER_BP]:
    assets.save_asset(path, only_if_is_dirty=False)

unreal.log_warning("SETUP done")
