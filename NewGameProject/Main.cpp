# include <Siv3D.hpp>
# include "TextureManager.hpp"
# include "MapCreator.hpp"
# include "PlayerManager.hpp"
# include "TimeManager.hpp"
# include "Player.hpp"
# include "Enemy.hpp"
# include "CalcHelper.hpp"
# include "PlayerAnimeManager.hpp"
# include "MapCollisionDetection.hpp"
# include "ObjectCollisionDetection.hpp"
# include "MapScreenHelper.hpp"
# include "BulletManager.hpp"
# include "EnemyAnimeManager.hpp"
# include "GameObj.hpp"
# include "EnemyManager.hpp"

void Main()
{
    Window::SetPos(0, 0);
    // 2021/01/11 コード整理
    Player player;
    Texture mapTexture2(U"map/customTileset.png");
    // 2021/01/11 ↑までコード整理済
    Array<MapObjectTip> mapObjectTips = MapCreator::GetMapObjectTip();
    MapCollisionDetection mapCollisionDetection;
    ObjectCollisionDetection objectCollisionDetection;
    MapScreenHelper mapScreenHelper;
    Effect effect;
    PlayerManager playerManager;
    EnemyManager enemyManager;
    TimeManager timeManager;
    PlayerAnimeManager playerAnimeManager;
    EnemyAnimeManager enemyAnimeManager;
    GameObj gameObj;
    while (System::Update())
    {
        #ifdef _DEBUG
        player.Debug(gameObj.font);
        gameObj.font(Cursor::Pos()).draw(600, 0);
        #endif _DEBUG
        // 初期化処理
        gameObj.Init(player);
        gameObj.DisplayAnimeTypeForDebug(Vec2(600, 70));
        // プレイヤーのアクション
        playerManager.Action(player, timeManager, gameObj.mapTips);
        // バレット処理
        gameObj.BulletAction(player, gameObj, timeManager);
        // マップのあたり判定
        mapCollisionDetection.CheckWall(gameObj.mapTips, player, mapScreenHelper);
        // あたり判定
        objectCollisionDetection.Check(mapObjectTips, player, mapScreenHelper, timeManager);
        // ストップウォッチ系の管理
        timeManager.Control(player);

        Vec2 screenOriginPosition(MapScreenHelper::ChangeWorldToScreenPos(player.pos));
        MapTip::DrawMapTipTextures(gameObj.mapTips, mapTexture2, screenOriginPosition, gameObj.smallFont);
        MapObjectTip::SetMapObjectTip(mapObjectTips, mapTexture2, screenOriginPosition);
        // プレイヤーのアニメーション描画
        playerAnimeManager.Draw(player, timeManager, effect);
        // デバッグ用
        player.DrawDetection();
        // 敵のアクション
        enemyManager.Action(gameObj);
        // 敵の描画
        enemyManager.Draw(enemyAnimeManager, gameObj, player);
    }
}

// 11/12
// カメラの固定関係の実装でバグが発生するかも
// 頂上のy軸を超えた時, x軸の右側最短とか確認していない
// IsMoveCameraX,Yメソッドが肝心