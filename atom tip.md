#markdown tip

## reval.js slide功能笔记
#### 1.通过front-matter设置slide
- 将需要的设置写在presentation下
e.g.:
```
---
presentation:
  width: 1800
  height: 1200
  controls: true
---
```
#### 2.编写slide
```
<!-- slide -->
<!-- slide data-notes="Write your note here" --> //演讲提示页面，默认是隐藏的,html用法是在<section></section>里面加上一对<aside></aside>
<!-- slide vertical=true --> //添加纵向slide
<!-- slide id="my-id" class="my-class1 my-class2" -->
<!-- slide data-background-color="#ffffff" -->
```
- Ctrl+Shift+P 输入 insert
- slide可添加backgrounds：
  data-background-color/image/size/position/repeat"":修改slide背景颜色/添加URL或本地照片/尺寸/锚点/
  data-background-video/video-loop/video-muted/size"": 添加背景视频
  data-background-iframe = “ https://slides.com ”  data-background-interactive：添加网页作为slide背景，interactive可以与背景互动
  data-background-transition""：背景转换可选 none/fade/slide/convex/concave/zoom


#### 3.片段样式
- 有时候不希望页面内容一次性全部显示，需要逐条目, 逐项地出现只要为页面元素添加一个class="fragment"就可以做到
- data-fragment-index属性可以让片段逐条出现

```
Item 1 <!-- .element: class="fragment" data-fragment-index="1" -->
Item 2 <!-- .element: class="fragment" data-fragment-index="2" -->
<p class="fragment grow">增大</p>
<p class="fragment shrink">缩小</p>
<p class="fragment fade-out">阅后消失</p>
<p class="fragment fade-up">向上出现</p>
<p class="fragment fade-right">向右出现</p>
<p class="fragment current-visible">仅显示当前条目</p>
<p class="highlight-current-blue">仅当前条目为蓝色</p>
```
#### 4.页面切换方式
- 利用data-transition定义<section>切换方式，利用data-transition-speed属性定义切换速度
- 在presentation里写入 none/fade/slide/convex/concave/zoom
  data-transition = “ slide-in fade-out ”

#### 5.页面锚点
```
<a href="#/8/2">点击到达第8页的第2个子页面<a>
<a href="#/some">点击到达id是some的<section><a>
<a href="#" class="navigate-left">点击向左<a>
<a href="#" class="navigate-right">点击向右<a>
<a href="#" class="navigate-up">点击向上<a>
<a href="#" class="navigate-down">点击向下<a>
<a href="#" class="navigate-prev">点击至上一页<a>
<a href="#" class="navigate-next">点击至下一页<a>
```

#### 6.丰富的快捷键，为演示PPT提供方便
  全屏 f , 退出全屏 Esc
  上一页 p, 下一页 n/空格
  首页 Home, 末页 End
  缩略图 Esc 或 o
  黑屏 b
  演讲提示模式 s
  vi导航键: h, j, k, l
  帮助页面: ?

#### 7.框架主题包
<link rel="stylesheet" href="~/github/eveal.js/css/theme/black.css" id="theme">
  black: Black background, white text, blue links (default theme)
  white: White background, black text, blue links
  league: Gray background, white text, blue links (default theme for reveal.js < 3.0.0)
  beige: Beige background, dark text, brown links
  sky: Blue background, thin dark text, blue links
  night: Black background, thick white text, orange links
  serif: Cappuccino background, gray text, brown links
  simple: White background, black text, blue links
  solarized: Cream-colored background, dark green text, blue links

#### 8.高级用法
  width/height: silde宽度和高度
  margin：边框宽度
  minScale/maxScale：最大最小slide比例
  controls: true 在每页右下角显示浏览方向按钮
  progress: true   在页面底部显示浏览进度条
  slideNumber: false   当前页码
  history: false   将每页记slide录在浏览记录里
  keyboard: true   启用键盘快捷键
  overview: true   启用缩略图模式(按o/Esc键)
  center: true   垂直方向居中(false:顶部)
  touch: true   支持触摸屏
  loop: false   循环播放
  rtl: false   文字显示和播放顺序改为从右到左(right to left)
  shuffle: false   随机加载下一页
  fragments: true   全局关闭片段功能
  embedded: false   表示当前幻灯片嵌在另一个网页中
  help: true   按问号(?)键显示帮助信息
  showNotes: false   演讲者笔记对听众可见
  autoPlayMedia: null   自动播放媒体
  // Global override for autolaying embedded media (video/audio/iframe)
	// - null: Media will only autoplay if data-autoplay is present
	// - true: All media will autoplay, regardless of individual setting
	// - false: No media will autoplay, regardless of individual setting
  autoSlide: 0   等待n毫秒后自动前进到下一页, 0表示禁用
  autoSlideStoppable: true   允许禁用自动播放
  autoSlideMethod: Reveal.navigateNext   自动播放所用
  mouseWheel: false   支持鼠标滚轮浏览
  hideAddressBar: true   在移动设备上自动隐藏地址栏
  previewLinks: false   将超链接显示在一个浮层里
  transition: 'default'   全局设置页面切换方式
  transitionSpeed: 'default'   全局设置页面切换速度
  backgroundTransition: 'default'   全局设置背景切换方式
  viewDistance: 3   距离当前页的可见范围
  parallaxBackgroundImage: ''   视差背景图地址
  parallaxBackgroundSize: ''   视差背景图尺寸
  parallaxBackgroundHorizontal: null   背景水平移动速度
  parallaxBackgroundVertical: null   背景垂直移动速度

<!-- pagebreak -->

---
    - presentation:
      The "normal" size of the presentation, aspect ratio will be preserved
      # when the presentation is scaled to fit different resolutions. Can be
      # specified using percentage units.
      width: 960
      height: 700

      # Factor of the display size that should remain empty around the content
      margin: 0.1

      # Bounds for smallest/largest possible scale to apply to content
      minScale: 0.2
      maxScale: 1.5

      # Display controls in the bottom right corner
      controls: true

      # Display a presentation progress bar
      progress: true

      # Display the page number of the current slide
      slideNumber: false

      # Push each slide change to the browser history
      history: false

      # Enable keyboard shortcuts for navigation
      keyboard: true

      # Enable the slide overview mode
      overview: true

      # Vertical centering of slides
      center: true

      # Enables touch navigation on devices with touch input
      touch: true

      # Loop the presentation
      loop: false

      # Change the presentation direction to be RTL
      rtl: false

      # Randomizes the order of slides each time the presentation loads
      shuffle: false

      # Turns fragments on and off globally
      fragments: true

      # Flags if the presentation is running in an embedded mode,
      # i.e. contained within a limited portion of the screen
      embedded: false

      # Flags if we should show a help overlay when the questionmark
      # key is pressed
      help: true

      # Flags if speaker notes should be visible to all viewers
      showNotes: false

      # Number of milliseconds between automatically proceeding to the
      # next slide, disabled when set to 0, this value can be overwritten
      # by using a data-autoslide attribute on your slides
      autoSlide: 0

      # Stop auto-sliding after user input
      autoSlideStoppable: true

      # Enable slide navigation via mouse wheel
      mouseWheel: false

      # Hides the address bar on mobile devices
      hideAddressBar: true

      # Opens links in an iframe preview overlay
      previewLinks: false

      # Transition style
      transition: 'default' # none/fade/slide/convex/concave/zoom

      # Transition speed
      transitionSpeed: 'default' # default/fast/slow

      # Transition style for full page slide backgrounds
      backgroundTransition: 'default' # none/fade/slide/convex/concave/zoom

      # Number of slides away from the current that are visible
      viewDistance: 3

      # Parallax background image
      parallaxBackgroundImage: '' # e.g. "'https://s3.amazonaws.com/hakim-static/reveal-js/reveal-parallax-1.jpg'"

      # Parallax background size
      parallaxBackgroundSize: '' # CSS syntax, e.g. "2100px 900px"

      # Number of pixels to move the parallax background per slide
      # - Calculated automatically unless specified
      # - Set to 0 to disable movement along an axis
      parallaxBackgroundHorizontal: null
      parallaxBackgroundVertical: null

      # Parallax background image
      parallaxBackgroundImage: '' # e.g. "https://s3.amazonaws.com/hakim-static/reveal-js/reveal-parallax-1.jpg"

      # Parallax background size
      parallaxBackgroundSize: '' # CSS syntax, e.g. "2100px 900px" - currently only pixels are supported (don't use % or auto)

      # Number of pixels to move the parallax background per slide
      # - Calculated automatically unless specified
      # - Set to 0 to disable movement along an axis
      parallaxBackgroundHorizontal: 200
      parallaxBackgroundVertical: 50

      # Enable Speake Notes
      enableSpeakerNotes: false
---

<!-- slide data-background-iframe="https://slides.com" data-background-interactive -->
