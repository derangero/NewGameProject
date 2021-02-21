# include <Siv3D.hpp>
# include "TextureManager.hpp"
# include "MapCreator.hpp"
# include "PlayerManager.hpp"
# include "TimeManager.hpp"
# include "Player.hpp"
# include "Enemy.hpp"
# include "CalcHelper.hpp"
# include "PlayerAnimeManager.hpp"
# include "MapCollisionHelper.hpp"
# include "ObjectCollisionHelper.hpp"
# include "MapScreenHelper.hpp"
# include "BulletManager.hpp"
# include "EnemyAnimeManager.hpp"
# include "GameObj.hpp"
# include "EnemyManager.hpp"
# include "GameEndManager.hpp"
# include "GameEffectManager.hpp"

#ifdef _DEBUG
#endif _DEBUG

void Main()
{
    Window::SetPos(0, 0);
    // 2021/01/11 コード整理
    Player player;
    Texture mapTexture2(U"map/customTileset.png");
    Texture waku1(U"image/waku1.png");
    Texture hurt(U"image/hurt.png");
    Texture emptyHurt(U"image/empty_hurt.png");
    // 2021/01/11 ↑までコード整理済
    MapCreator mapCreator(mapTexture2);
    MapCollisionHelper mapCollisionHelper(mapCreator);
    //ObjectCollisionHelper objectCollisionHelper;
    MapScreenHelper mapScreenHelper;
    Effect effect;
    PlayerManager playerManager;
    EnemyManager enemyManager;
    TimeManager timeManager;
    PlayerAnimeManager playerAnimeManager;
    EnemyAnimeManager enemyAnimeManager;
    GameEndManager gameEndManager;
    GameObj gameObj(mapCreator, player.spriteImageMetaDataMap);
    GameEffectManager effectManager;
    while (System::Update())
    {
        // 背景描画
        mapCreator.DrawBackGround();
        #ifdef _DEBUG
        player.Debug(gameObj.font);
        gameObj.font(Cursor::Pos()).draw(600, 0);
        gameObj.font(Format(U"getCoin: ", player.coinCount)).draw(600, 20);
        // 複合するEnum増やす　
        //int singleAction = player.walkFlag + player.crouchFlag + player.jumpFlag + player.dashFlag;
        //if (singleAction > 1) {
        //    auto a = 0;
        //}
        #endif _DEBUG
        gameObj.Init(player);
        /** デバッグ用 */
        gameObj.DisplayAnimeTypeForDebug(Vec2(600, 70));
        // プレイヤーのアクション
        playerManager.Action(player, timeManager, mapCreator.mapTips);
        // バレット処理
        gameObj.BulletAction(player, gameObj, timeManager);

        // マップのあたり判定
        // 一応、キャラの移動は判定前が前提
        mapCollisionHelper.CheckCollision(player, mapScreenHelper);
        mapCollisionHelper.CheckBlockCollision(player, mapScreenHelper);
        // ストップウォッチ系の管理
        timeManager.Control(player);

        // ワールド座標からスクリーン座標に変換する
        Vec2 screenOriginPosition(MapScreenHelper::ChangeWorldToScreenPos(player.pos));
        // マップチップ描画
        MapTip::DrawMapTipTextures(mapCreator.mapTips, mapTexture2, screenOriginPosition, gameObj.smallFont);
        // オブジェクトチップ描画
        mapCreator.DrawObjectTip(mapTexture2, screenOriginPosition, timeManager, player);
        // デバッグ用
        player.DrawDetection();

        // 敵のアクション
        enemyManager.Action(gameObj, player);
        // (敵)マップのあたり判定
        for (Enemy& enemy : gameObj.enemies) {
            mapCollisionHelper.CheckCollision(enemy, mapScreenHelper);
            enemy.beforeHitBox = enemy.hitBox;
        }
        // 敵の描画
        enemyManager.Draw(enemyAnimeManager, gameObj, player);

        // プレイヤーのアニメーション描画
        playerAnimeManager.Draw(player, timeManager, effect);
        // HP周りのUI
        waku1.draw(280, 10);
        for (int i : step(player.hp)) {
            hurt.draw(390 + (i * 30), 33);
        }
        for (int i : step(player.damaged)) {
            emptyHurt.draw(450 - (i * 30), 33);
        }
        // ゲームオーバーの処理
        gameEndManager.DrawScene(player, playerAnimeManager, timeManager, effect, effectManager);
        
        // HPが低いときの画面エフェクト
        // Scene::Center()注意
        if (player.hp < PLAYER_DANGER_HP && player.hp > 0) {
           Shape2D::NStar(550, 450, 480, Scene::Center()).draw(Color(255, 77, 77, 0 + int32(40.0 * Periodic::Sine0_1(2s))));
        }
        player.beforeHitBox = player.hitBox;
    }
}

// 11/12
// カメラの固定関係の実装でバグが発生するかも
// 頂上のy軸を超えた時, x軸の右側最短とか確認していない
// IsMoveCameraX,Yメソッドが肝心