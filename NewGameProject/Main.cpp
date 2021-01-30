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
# include "GameOverManager.hpp"

void Main()
{
    Window::SetPos(0, 0);
    // 2021/01/11 コード整理
    Player player;
    Texture mapTexture2(U"map/customTileset.png");
    // 2021/01/11 ↑までコード整理済
    MapCreator mapCreator(mapTexture2);
    MapCollisionDetection mapCollisionDetection;
    ObjectCollisionDetection objectCollisionDetection;
    MapScreenHelper mapScreenHelper;
    Effect effect;
    PlayerManager playerManager;
    EnemyManager enemyManager;
    TimeManager timeManager;
    PlayerAnimeManager playerAnimeManager;
    EnemyAnimeManager enemyAnimeManager;
    GameOverManager gameOverManager;
    GameObj gameObj(mapCreator, player.spriteImageMetaDataMap);
    while (System::Update())
    {
        #ifdef _DEBUG
        player.Debug(gameObj.font);
        gameObj.font(Cursor::Pos()).draw(600, 0);
        gameObj.font(player.crouchFlag).draw(600, 20);
        #endif _DEBUG
        // 初期化処理
        gameObj.Init(player);
        gameObj.DisplayAnimeTypeForDebug(Vec2(600, 70));
        // プレイヤーのアクション
        playerManager.Action(player, timeManager, mapCreator.mapTips);
        // バレット処理
        gameObj.BulletAction(player, gameObj, timeManager);
        // マップのあたり判定
        // 一応、キャラの移動は判定前が前提
        mapCollisionDetection.CheckWall(gameObj.mapCreator.mapTips, player, mapScreenHelper);
        // あたり判定
        objectCollisionDetection.Check(mapCreator, player, mapScreenHelper, timeManager);
        // ストップウォッチ系の管理
        timeManager.Control(player);

        Vec2 screenOriginPosition(MapScreenHelper::ChangeWorldToScreenPos(player.pos));
        MapTip::DrawMapTipTextures(mapCreator.mapTips, mapTexture2, screenOriginPosition, gameObj.smallFont);
        
        mapCreator.SetObjectTip(mapTexture2, screenOriginPosition);
        // デバッグ用
        player.DrawDetection();
        // 敵のアクション
        enemyManager.Action(gameObj, player);
        // 敵の描画
        enemyManager.Draw(enemyAnimeManager, gameObj, player);
        // プレイヤーのアニメーション描画
        playerAnimeManager.Draw(player, timeManager, effect);
        // ゲームオーバーの処理
        gameOverManager.DrawScene(player, playerAnimeManager, timeManager, effect);
        
        // HPが低いときの画面エフェクト
        // Scene::Center()注意
        if (player.hp < PLAYER_DANGER_HP && player.hp > 0) {
           Shape2D::NStar(550, 450, 480, Scene::Center()).draw(Color(255, 77, 77, 0 + int32(40.0 * Periodic::Sine0_1(2s))));
        }
    }
}

// 11/12
// カメラの固定関係の実装でバグが発生するかも
// 頂上のy軸を超えた時, x軸の右側最短とか確認していない
// IsMoveCameraX,Yメソッドが肝心